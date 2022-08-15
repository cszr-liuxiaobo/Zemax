#include "stdafx.h"
#include "basesetting.h"
#include <stdio.h>
#include<stdlib.h>
#include<typeinfo>
#include <QtCore/qobjectdefs.h>

using namespace std;

//***************创建应用区*******************
void ZemaxProject::createApplication() {
    //加载软件

    CoInitialize(NULL);
    // Create the initial connection class   
    IZOSAPI_ConnectionPtr TheConnection(__uuidof(ZOSAPI_Connection));
    // Attempt to create a Standalone connection
    TheApplication = TheConnection->CreateNewApplication();
    //TheApplication->LicenseStatus= LicenseStatusType(5);
    
    if (TheApplication == nullptr)
    {
        handleError("An unknown error occurred!");
        //return -1;
    }
    VARIANT_BOOL ValidLicense = TheApplication->IsValidLicenseForAPI;
    //TheApplication->IsValidLicenseForAPI = -1;
    cout <<"ValidLicense:::"<< ValidLicense << endl;
    // Check the connection status
    if (!TheApplication->IsValidLicenseForAPI)
    {
        handleError("License check failed!");
        //return -1;
    }
    if (TheApplication->Mode != ZOSAPI_Mode::ZOSAPI_Mode_Server)
    {
        handleError("Standlone application was started in the incorrect mode!");
        //return -1;
    }
    // Set up primary optical system初始化
// 28615 IOpticalSystem : IDispatch 按照指针路线去思考问题。一路跟着指针走。
    TheSystem = TheApplication->PrimarySystem;
    sampleDir = TheApplication->SamplesDir;     //存放zmx文件的地方
    outputFolder = sampleDir + "\\output/";
}
//加载.zmx镜头文件
int ZemaxProject::loadmyFile(_bstr_t inputFile) {
    //// creates a new API directory
    /*step0:打开任意一个镜头文件*/
    //注意判断加载的文件是否存在。
    if (!fileExists(inputFile)) {
        cout << "You need to run THE Example before running this example" << endl;
#if defined(_DEBUG)
        // keeps console open when in debug mode
        system("pause");
#endif
        return 0;
    }
    TheSystem->LoadFile(inputFile, false);

    max_wave = TheSystem->SystemData->Wavelengths->NumberOfWavelengths;
    // 获取主波及其波长数据
    for (int a = 1; a <= max_wave; a++) {
        if (TheSystem->SystemData->Wavelengths->GetWavelength(a)->IsPrimary)
            initpwav = a;
    }

    ////此处可以将第一条wave设置为Primary。务必在loadmyFile之后进行。
    //TheSystem->SystemData->Wavelengths->GetWavelength(1)->MakePrimary();

    //如果文件有问题加一层判断。if error 返回错误。    VARIANT_BOOL LoadFile
    return 1;
}

int ZemaxProject::createDirectory(std::string path)
{
    int len = path.length();
    char tmpDirPath[256] = { 0 };
    for (int i = 0; i < len; i++)
    {
        tmpDirPath[i] = path[i];
        if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
        {
            if (_access(tmpDirPath, 0) == -1)
            {
                int ret = _mkdir(tmpDirPath);
                if (ret == -1) return ret;
            }
        }
    }
    return 0;
}


//***************预设和预获参数区***************
//预设系统初始必要参数。如explore中的rayAiming等。
void ZemaxProject::basicSetting() {
    cout << "outputFolder::" << outputFolder << endl;
    //if (0 != _access(outputFolder.c_str(), 0))
    //{
    //    // if this folder not exist, create a new one.

    //    if (createDirectory(outputFolder))   // return 0, if successfully created
    //    {
    //        fprintf(stderr, "error: cannot create folder '%s', ", outputFolder.c_str());
    //        fprintf(stderr, "in File '%s', line %d. \n", __FILE__, __LINE__);
    //        exit(1);
    //    }
    //}
    
    //sampleDir = outputFolder.c_str();
    //_bstr_t creatdir = "E:\\ZemaxProject\\output";   //可以自己指定位置
    TheAnalyses = TheSystem->Analyses;
    sysWave = TheSystem->SystemData->Wavelengths;
    TheMFE = TheSystem->MFE;
    //int num_fields = TheSystem->SystemData->Fields->NumberOfFields;
    TheLDE = TheSystem->LDE;
    //设置ray aiming
    TheSystem->SystemData->RayAiming->PutRayAiming(RayAimingMethod_Real);
}

void ZemaxProject::propertySetting() {
    //基础设置1
    Surface_0 = TheLDE->GetSurfaceAt(0);
    stopsurface = TheLDE->StopSurface;
    //cout << "stopsurface===============" << stopsurface << endl;
    Surface_stop = TheLDE->GetSurfaceAt(stopsurface);
    SurfacesNum = TheLDE->NumberOfSurfaces;
    Surface_Lastglass = TheLDE->GetSurfaceAt(SurfacesNum - 2);
    Surface_Last = TheLDE->GetSurfaceAt(SurfacesNum - 1);
    max_num_field = TheSystem->SystemData->Fields->NumberOfFields;   ///指导寻址到最后才确认数据类型;指针最终指向的是类，所以从类上找下属的函数属性等
    cout << "max_num_field:::"<< max_num_field << endl;
//最大fieldX/fieldY值

    //物距就是第一个面的距离
    Object_distance = Surface_0->Thickness;
    //获取ImageHeight最大值及其下标。
    initialfieldtype = TheSystem->SystemData->Fields->GetFieldType();

    initialfieldYmaxvalue = TheSystem->SystemData->Fields->GetField(max_num_field)->Y;

    TheSystem->SystemData->Fields->ConvertToFieldType(FieldType::FieldType_ParaxialImageHeight);
    std::vector<double> ParaxialImageHeight; //相当于python的list，设置容器，存储double类型数据。
    for (int i = 1; i <= max_num_field; i++) {
        double ParaxialImageHeight_y = TheSystem->SystemData->Fields->GetField(i)->Y;
        ParaxialImageHeight.push_back(ParaxialImageHeight_y);
    }
    double max = -999;
    for (auto v : ParaxialImageHeight) {
        if (max < v) max = v;
    }

    SystemImageheightMax = max;
    auto distance = find(ParaxialImageHeight.begin(), ParaxialImageHeight.end(), max);
    SystemImageheightMaxIndex = distance - ParaxialImageHeight.begin()+1;

    TheSystem->SystemData->Fields->ConvertToFieldType(initialfieldtype);


    max_wave = TheSystem->SystemData->Wavelengths->NumberOfWavelengths;
    // 获取主波及其波长数据
    for (int a = 1; a <= TheSystem->SystemData->Wavelengths->NumberOfWavelengths; a++) {
        if (TheSystem->SystemData->Wavelengths->GetWavelength(a)->IsPrimary)
            pwav = a;
    }
}

//makeYourSetting::
// 人工设定所需的参数。如设定imageheight及wavelength取值范围
//基本逻辑：每次对这些设定数据的变更都会被长久保存，所以需要设定数据时就调用一下。
unsigned int ZemaxProject::set_WL_NUM(unsigned int num) { WL_NUM = num; return WL_NUM; }
double ZemaxProject::set_WL_MIN(double param) { WL_MIN = param; return WL_MIN; }
double ZemaxProject::set_WL_MAX(double param) { WL_MAX = param; return WL_MAX; }
unsigned int ZemaxProject::set_IMGHT_NUM(unsigned int num) { IMGHT_NUM = num; return IMGHT_NUM; }
double ZemaxProject::set_IMGHT_MIN(double param) { IMGHT_MIN = param; return IMGHT_MIN; }
double ZemaxProject::set_IMGHT_MAX(double param) { IMGHT_MAX = param; return IMGHT_MAX; }
unsigned int ZemaxProject::set_IMGWT_NUM(unsigned int num) { IMGWT_NUM = num; return IMGWT_NUM; }
double ZemaxProject::set_IMGWT_MIN(double param) { IMGWT_MIN = param; return IMGWT_MIN; }
double ZemaxProject::set_IMGWT_MAX(double param) { IMGWT_MAX = param; return IMGWT_MAX; }

//然后统一获取设定的参数，注意对应的下标就可以。
vector<ANYData> ZemaxProject::getYourSetting() {
    vector<ANYData>  params_setting;
    params_setting.push_back(ANYData(WL_NUM));
    params_setting.push_back(ANYData(WL_MIN));
    params_setting.push_back(ANYData(WL_MAX));
    params_setting.push_back(ANYData(IMGHT_NUM));
    params_setting.push_back(ANYData(IMGHT_MIN));
    params_setting.push_back(ANYData(IMGHT_MAX));
    return params_setting;
}

//获取基础参数，一旦field或wavelength等的更新随时都可以调用此函数
vector<DATA> ZemaxProject::getLensProperties() {
    /*step2:获取focalLength, effectiveFocalLength*/
    TheSystem->LDE->GetFirstOrderData(&EFL, &paraxialWorkingFNumber, &realWorkingFNumber, &paraxialImageHeight, &paraxialMagnification);
    //*****************************************************************************************************
    /*step3:获取FNumber光圈，effectiveFNumber---realWorkingFNumber，paraxialWorkingFNumber*/
    //*****************************************************************************************************
    /*step4:设置理想像高，并获取理想像高的实际像高ParaxialImageHeight*/

     //存储的顺序：WL_NUM WL_MIN WL_MAX IMGHT_NUM IMGHT_MIN IMGHT_MAX
    vector<ANYData>  params_setting = getYourSetting();
    
    unsigned int WL_NUM = params_setting[0].uival;
    double WL_MIN = params_setting[1].dval;
    double WL_MAX = params_setting[2].dval;
    unsigned int IMGHT_NUM = params_setting[3].uival;
    double IMGHT_MIN = params_setting[4].dval;
    double IMGHT_MAX = params_setting[5].dval;

    //--------------------------------------------------------------------------------
    //输出更改物距后所需参数的变化(注意提前将镜头的其他参数进行固定)
    //固定其他的镜头参数
    for (int i = 2; i < SurfacesNum; i++) {
        ILDERowPtr surface_i = TheLDE->GetSurfaceAt(i);
        ISolveDataPtr Solver_i = surface_i->RadiusCell->CreateSolveType(SolveType_Fixed);
        ISolveDataPtr Solveri = surface_i->ThicknessCell->CreateSolveType(SolveType_Fixed);
    }

    //输出所有基础数据结果，指标储存数据到txt文件
    fstream textfile_Baseparameters;
    string filepath_Baseparameters = (_bstr_t)outputFolder.c_str() +"\\"+ file_name + ".txt";
    textfile_Baseparameters.open(filepath_Baseparameters, fstream::trunc | ios::out);
    //--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
    double dW = (WL_MAX - WL_MIN) / (WL_NUM - 1);
    textfile_Baseparameters << "LensPath= " << inputFile << endl;
    textfile_Baseparameters << "lensFile= " << file_name+".zmx" << endl;
    textfile_Baseparameters << "Wave= " << WL_MIN << ":" << dW << ":" << WL_MAX << "     % WAVELENGTH SAMPLES (UM)" << endl;
    textfile_Baseparameters << "ImgHeightNum= " << IMGHT_NUM << "     % Number of IMAGE HEIGHTS" << endl;
    textfile_Baseparameters << "ImageHeightMax= " << IMGHT_MAX << "     % Maximum IMAGE HEIGHT (mm)" << endl;
    textfile_Baseparameters << "ObjectDistance= " << Surface_0->Thickness << "     % OBJECT DISTANCE (MM)" << endl;
    textfile_Baseparameters << "Magnification= " << paraxialMagnification << "     % OPTICAL SYSTEM MAGNIFICATION" << endl;
    //outFile << "baseLensFileName= " << "--" << endl;

    //获取主波波长
    textfile_Baseparameters << "PrimaryWave= " << pwav << "  value=" << sysWave->GetWavelength(pwav)->Wavelength << "    % REFERENCE WAVELENGTH (NM)" << endl;
    textfile_Baseparameters << "Half FOV_y=" << (TheSystem->SystemData->Fields->GetField(max_num_field)->Y) << "     % MAXIMUM DIAGONAL HALF FOV (DEGREE)" << endl;
    textfile_Baseparameters << "EFL= " << EFL << "     % EFFECTIVE FOCAL LENGTH" << endl;
    textfile_Baseparameters << "fnumber_eff=realWorkingFNumber= " << realWorkingFNumber << "       % EFFECTIVE F-NUMBER" << endl;
    textfile_Baseparameters << "fnumber=paraxialWorkingFNumber= " << paraxialWorkingFNumber << "      % F-NUMBER" << endl;
    //各种常用类型都进行保留，用不到的就设为NULL。
    DATA data[99] = { {"LensPath",NULL,NULL,(string)inputFile},
            {"ObjectDistance",NULL,Surface_0->Thickness,"NULL"},
            {"mag",NULL,paraxialMagnification,"NULL"},
            {"PrimaryWave",pwav,NULL,"NULL"},
            {"PrimaryWavelength(nm)",NULL,sysWave->GetWavelength(pwav)->Wavelength,"NULL"},
            {"Half FOV_y(degree)",NULL,TheSystem->SystemData->Fields->GetField(max_num_field)->Y,"NULL"},
            {"EFL(mm)",NULL,EFL,"NULL"},
            {"realWorkingFNumber",NULL,realWorkingFNumber,"NULL"},
            {"paraxialWorkingFNumber",NULL,paraxialWorkingFNumber,"NULL"},
    };

    vector<DATA> MYDATA;
    for (int i=0; i < 9;i++) {
        MYDATA.push_back(data[i]);
    }
    return MYDATA;
}
void ZemaxProject::add_w_f_field(mxArray* x) {
    mxAddField(x, "fieldHeight");
    mxArray* pMxArray1;
    pMxArray1 = mxCreateNumericMatrix(IMGHT_NUM, 1, mxDOUBLE_CLASS, mxREAL);
    double* pData1 = mxGetPr(pMxArray1);
    for (int J = 1; J <= IMGHT_NUM; J++) {
        double IMGHT = IMGHT_MIN + (J - 1) * (IMGHT_MAX - IMGHT_MIN) / (IMGHT_NUM - 1);
        pData1[J - 1] = IMGHT;
    }
    mxSetField(x, 0, "fieldHeight", pMxArray1);

    mxAddField(x, "wavelength");
    mxArray* pMxArray2;
    pMxArray2 = mxCreateNumericMatrix(WL_NUM, 1, mxDOUBLE_CLASS, mxREAL);
    double* pData2 = mxGetPr(pMxArray2);
    for (int I = 1; I <= WL_NUM; I++) {
        double WLT = WL_MIN + (I - 1) * (WL_MAX - WL_MIN) / (WL_NUM - 1);
        pData2[I - 1] = WLT;
    }
    mxSetField(x, 0, "wavelength", pMxArray2);
}

void ZemaxProject::Distorition_result(IAR_Ptr distortion_Results) {
    for (int i = 0; i < distortion_Results->NumberOfDataSeries; i++) {
        IAR_DataSeriesPtr dataseries = distortion_Results->GetDataSeries(i);
        for (int j = 0; j < dataseries->NumSeries; j++) {
            if (j == 2) {
                for (int k = 0; k < dataseries->GetXData()->Length; k++) {
                    if (k == dataseries->GetXData()->Length - 1) {
                        //textfile_dis << scientific << setprecision(6) << dataseries->GetXData()->GetValueAt(k) << "\t";
                        //textfile_dis << scientific << setprecision(6) << dataseries->GetYData()->GetValueAt(k, j) << endl;
                        distoritiondata[0] = dataseries->GetYData()->GetValueAt(k, j);
                    }
                }
            }
        }
    }
}
////用于单纯的实现zemax的distortion功能
//distortion分析的设置和结果单列出来，用户可以根据需要修改imageheight，指定某个wavelength进行计算。
void ZemaxProject::Distorition_setting(double WLT, double IMGHT, double IMGWT, int whichwave, int Fieldtype, int Distortiontype, int Scantype) {
    TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)Fieldtype); //人为设定的类型
    sysWave->GetWavelength(whichwave)->Wavelength = WLT; //参考波长可根据需求设计添加
    TheSystem->SystemData->Fields->GetField(SystemImageheightMaxIndex)->X = IMGWT;
    TheSystem->SystemData->Fields->GetField(SystemImageheightMaxIndex)->Y = IMGHT;
    TheSystem->SystemData->Fields->SetVignetting();

    IA_Ptr distortion=TheAnalyses->New_FieldCurvatureAndDistortion();
    IAS_FieldCurvatureAndDistortionPtr DistortionSettings = distortion->GetSettings();
    DistortionSettings->Wavelength->SetWavelengthNumber(whichwave);
    DistortionSettings->PutDistortion((Distortions)Distortiontype);  //Distortions_F_TanTheta
    DistortionSettings->PutScanType((FieldScanDirections)Scantype);  //FieldScanDirections_Plus_Y
    DistortionSettings->PutIgnoreVignette(FALSE);
    distortion->ApplyAndWaitForCompletion();
    IAR_Ptr distortion_Results = distortion->GetResults();
    Distorition_result(distortion_Results);
    distortion->Close();
    TheSystem->SystemData->Fields->ConvertToFieldType(initialfieldtype);
}

//实现distortion的多个数据获取功能，设定最大最小波长，最大最小像高，以及设定fieldtype。
//whichwave没意义，直接指定为pwav。Scantype也直接指定，只留下Distortiontype
mxArray* ZemaxProject::DistortionMultiple(int whichwave, int Fieldtype, int Distortiontype, int Scantype) {
    //存储的顺序：WL_NUM WL_MIN WL_MAX IMGHT_NUM IMGHT_MIN IMGHT_MAX
    cout << "distortion processing..." << endl;
    TheSystem->SystemData->Fields->DeleteAllFields();
    TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)Fieldtype); //人为设定的类型
    cout << "Fieldtype::" << Fieldtype << endl;
    TheSystem->SystemData->Fields->SetVignetting();

    //逻辑是在指定的field内进行指定波长下的distortion计算
    //此处需要根据数据设定主波长的波长值
    //fstream textfile_dis;
    //filepath_dis =  (_bstr_t)outputFolder.c_str() + "\\" + file_name + "_distortion001.txt";
    //textfile_dis.open(filepath_dis, ios::binary | ios::out|ios::trunc);
    ////zemax通过analyses输出的数据有两种结构，一种是PSF为代表的NumberOfDataGrids结构，下边计算PSF有介绍，需要直接根据横轴纵轴长度获取；
    ////一种是此处Distortion为代表的NumberOfDataSeries结构，有分列获取的要求；
    IA_Ptr distortion = TheAnalyses->New_FieldCurvatureAndDistortion();

    //vector<double> distoritiondata;
    //直接打包成mat

    // add field 'Distorition'
    //mxArray* m_Distorition = mxCreateStructMatrix(1, 1, 0, nullptr);   //将定义转到matPackage.h

    mxAddField(m_Distorition, "whichwave");
    mxSetField(m_Distorition, 0, "whichwave", mxCreateString(to_string(whichwave).c_str()));

    mxAddField(m_Distorition, "FieldType");
    mxSetField(m_Distorition, 0, "FieldType", mxCreateString(fieldtype[Fieldtype].c_str()));

    mxAddField(m_Distorition, "Distortiontype");
    mxSetField(m_Distorition, 0, "Distortiontype", mxCreateString(distortiontype[Distortiontype].c_str()));
     
    mxAddField(m_Distorition, "Scantype");
    mxSetField(m_Distorition, 0, "Scantype", mxCreateString(scantype[Scantype].c_str()));

    add_w_f_field(m_Distorition);

    mxAddField(m_Distorition, "function");
    int row = IMGHT_NUM; int col = WL_NUM;
    mxArray* pMxArray1;
    pMxArray1 = mxCreateNumericMatrix(row, col, mxDOUBLE_CLASS, mxREAL);
    double* pData1= mxGetPr(pMxArray1);
    Distorition_ij = 0; 
    
    for (int J = 1; J <= IMGHT_NUM; J++) {
        double IMGHT = IMGHT_MIN + (J - 1) * (IMGHT_MAX - IMGHT_MIN) / (IMGHT_NUM - 1);
        for (int I = 1; I <= WL_NUM; I++) {
            if (breakflage) {  //通过其他线程改变共用变量breakflage，然后continue掉后续所有工作。
                Distorition_ij = Distorition_ij + 1;
                continue;
            }
            double WLT = WL_MIN + (I - 1) * (WL_MAX - WL_MIN) / (WL_NUM - 1);
            double IMGWT = 0;
            sysWave->GetWavelength(whichwave)->Wavelength = WLT; //参考波长可根据需求设计添加
            TheSystem->SystemData->Fields->GetField(1)->X = IMGWT;
            TheSystem->SystemData->Fields->GetField(1)->Y = IMGHT;

            IAS_FieldCurvatureAndDistortionPtr DistortionSettings = distortion->GetSettings();
            DistortionSettings->Wavelength->SetWavelengthNumber(whichwave);
            DistortionSettings->PutDistortion((Distortions)Distortiontype);  //Distortions_F_TanTheta
            DistortionSettings->PutScanType((FieldScanDirections)Scantype);  //FieldScanDirections_Plus_Y
            DistortionSettings->PutIgnoreVignette(FALSE);
            distortion->ApplyAndWaitForCompletion();
            IAR_Ptr distortion_Results = distortion->GetResults();
            Distorition_result(distortion_Results);
            pData1[(I-1)* row +(J-1)] = distoritiondata[0];
            Distorition_ij = Distorition_ij + 1;
            QApplication::processEvents();
        }
    }
    mxSetField(m_Distorition, 0, "function", pMxArray1);
    //textfile_dis.close();
    distortion->Close();
    TheSystem->SystemData->Fields->ConvertToFieldType(initialfieldtype);
    cout << "distortion finish..." << endl;
    return m_Distorition;
}

void ZemaxProject::ChiefRayAngle_result(double WLT, double IMGHT, double IMGWT, int whichwave, int Fieldtype, int x, int y) {
    //转换为rad弧度
    CRAdata[0] = 0.017453292519943295 * (TheMFE->GetOperandValue(MeritOperandType_RAID, TheLDE->NumberOfSurfaces - 1, pwav, x, y, 0, 0, 0, 0));
    //textfile_CRA << scientific << setprecision(6) << IMGHT << "     ";
    //textfile_CRA << scientific << setprecision(6) << TheMFE->GetOperandValue(MeritOperandType_RAID, TheLDE->NumberOfSurfaces - 1, pwav, x, y, 0, 0, 0, 0) << endl;
}
vector<double> ZemaxProject::ChiefRayAngle_setting(double WLT, double IMGHT, double IMGWT, int whichwave, int Fieldtype,int x,int y) {
    sysWave->GetWavelength(whichwave)->Wavelength = WLT; //参考波长可根据需求设计添加
    TheSystem->SystemData->Fields->GetField(1)->X = IMGWT;
    TheSystem->SystemData->Fields->GetField(1)->Y = IMGHT;
    TheSystem->SystemData->Fields->SetVignetting();
    //CRA = ACOS(RAYN(IMG_SURF_NUM))
    vector <double> cradata;
    cradata.push_back(IMGHT);cradata.push_back(TheMFE->GetOperandValue(MeritOperandType_RAID, TheLDE->NumberOfSurfaces - 1, whichwave, x, y, 0, 0, 0, 0));
    return cradata;
}
mxArray* ZemaxProject::ChiefRayAngleMultiple(int whichwave, int Fieldtype, int x, int y) {
    /*step7:获取chief ray angle*/
    cout << "ChiefRayAngle processing..." << endl;
    //filepath_CRA =  (_bstr_t)outputFolder.c_str() + "\\" + file_name + "_ChiefRayAngle001.txt";
    //textfile_CRA.open(filepath_CRA, ios::binary | ios::out | ios::trunc);
    //textfile_CRA << "Chief Ray Angle:                           " << endl;
    //直接打包成mat

    //// add field 'CRA'
    //mxArray* m_CRA = mxCreateStructMatrix(1, 1, 0, nullptr);

    mxAddField(m_CRA, "whichwave");
    mxSetField(m_CRA, 0, "whichwave", mxCreateString(to_string(whichwave).c_str()));

    mxAddField(m_CRA, "FieldType");
    mxSetField(m_CRA, 0, "FieldType", mxCreateString(fieldtype[Fieldtype].c_str()));

    mxAddField(m_CRA, "Direction");
    mxSetField(m_CRA, 0, "Direction", mxCreateString("y"));

    add_w_f_field(m_CRA);

    mxAddField(m_CRA, "function");
    int row = IMGHT_NUM; int col = WL_NUM;
    mxArray* pMxArray2= mxCreateNumericMatrix(row, col, mxDOUBLE_CLASS, mxREAL);
    double* pData2 = mxGetPr(pMxArray2);
    //pData1 = (double*)mxCalloc(row*col, sizeof(double));
    TheSystem->SystemData->Fields->DeleteAllFields();
    TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)Fieldtype); 
    CRA_ij = 0;
    for (int J = 1; J <= IMGHT_NUM; J++) {
        double IMGHT = IMGHT_MIN + (J - 1) * (IMGHT_MAX - IMGHT_MIN) / (IMGHT_NUM - 1);
        //cout << "IMGHT:::" << IMGHT << endl;
        for (int I = 1; I <= WL_NUM; I++) {
            if (breakflage) {  //通过其他线程改变共用变量breakflage，然后continue掉后续所有工作。
                CRA_ij += 1;
                continue;
            }
            double WLT = WL_MIN + (I - 1) * (WL_MAX - WL_MIN) / (WL_NUM - 1);
            ChiefRayAngle_setting(WLT, IMGHT,IMGWT_MIN, whichwave, Fieldtype);
            ChiefRayAngle_result(WLT, IMGHT, IMGWT_MIN, whichwave, Fieldtype);
            pData2[(I - 1) * row + (J - 1)] = CRAdata[0];
            CRA_ij += 1;
            QApplication::processEvents();
        }
    }
    //textfile_CRA.close();
    cout << "ChiefRayAngle finish!" << endl;
    TheSystem->SystemData->Fields->ConvertToFieldType(initialfieldtype);
    mxSetField(m_CRA, 0, "function", pMxArray2);
    return m_CRA;
}

void ZemaxProject::RI_result(double WLT, double IMGHT, double IMGWT, int whichwave, int Fieldtype, int samplenum) {
    RIdata[0] = TheMFE->GetOperandValue(MeritOperandType_RELI, samplenum, pwav, TheSystem->SystemData->Fields->NumberOfFields, 0, 0, 0, 0, 0);
    //textfile_RI << scientific << setprecision(6) << IMGHT << "    ";
    ////注意sample固定为10就可以了。
    //textfile_RI << scientific << setprecision(6) << TheMFE->GetOperandValue(MeritOperandType_RELI, samplenum, pwav, TheSystem->SystemData->Fields->NumberOfFields, 0, 0, 0, 0, 0) << endl;
}
void ZemaxProject::RI_setting(double WLT, double IMGHT, double IMGWT, int whichwave, int Fieldtype, int samplenum) {
    TheSystem->SystemData->Fields->DeleteAllFields();
    sysWave->GetWavelength(whichwave)->Wavelength = WLT; //参考波长可根据需求设计添加
    TheSystem->SystemData->Fields->GetField(1)->X = 0.0;
    TheSystem->SystemData->Fields->GetField(1)->Y = 0.0;
    TheSystem->SystemData->Fields->AddField(IMGWT, IMGHT, 1.0);
    TheSystem->SystemData->Fields->ClearVignetting();
    //cout << "fieldnumber:" << TheSystem->SystemData->Fields->NumberOfFields << "----" << "YYYYY:" << TheSystem->SystemData->Fields->GetField(2)->Y << "----" << "wavelength:" << WLT << endl;
    //CRA = ACOS(RAYN(IMG_SURF_NUM))
    //cout << scientific << setprecision(6) << IMGHT << "    ";
    //注意sample固定为10就可以了。
    //cout << scientific << setprecision(6) << TheMFE->GetOperandValue(MeritOperandType_RELI, samplenum, whichwave, TheSystem->SystemData->Fields->NumberOfFields, 0, 0, 0, 0, 0) << endl;
}
mxArray* ZemaxProject::RIMultiple(int whichwave, int Fieldtype) {
    //filepath_RI =  (_bstr_t)outputFolder.c_str() + "\\" + file_name + "_RI001.txt";
    //textfile_RI.open(filepath_RI, ios::binary | ios::out | ios::trunc);

    //直接打包成mat
    //// add field 'RI'
    //mxArray* m_RI = mxCreateStructMatrix(1, 1, 0, nullptr);
    mxAddField(m_RI, "whichwave");
    mxSetField(m_RI, 0, "whichwave", mxCreateString(to_string(whichwave).c_str()));

    mxAddField(m_RI, "FieldType");
    mxSetField(m_RI, 0, "FieldType", mxCreateString(fieldtype[Fieldtype].c_str()));

    mxAddField(m_RI, "Direction");
    mxSetField(m_RI, 0, "Direction", mxCreateString("y"));

    add_w_f_field(m_RI);
    mxAddField(m_RI, "function");
    int row = IMGHT_NUM; int col = WL_NUM;
    mxArray* pMxArray3 = mxCreateNumericMatrix(row, col, mxDOUBLE_CLASS, mxREAL);
    double* pData3 = mxGetPr(pMxArray3);
    cout << "Relative Illuminationm processing..." << endl;
    TheSystem->SystemData->Fields->DeleteAllFields();
    TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)Fieldtype);
    RI_ij = 0;
    for (int J = 1; J <= IMGHT_NUM; J++) {
        double IMGHT = IMGHT_MIN + (J - 1) * (IMGHT_MAX - IMGHT_MIN) / (IMGHT_NUM - 1);
        //cout << "IMGHT:::" << IMGHT << endl;
        for (int I = 1; I <= WL_NUM; I++) {
            if (breakflage) {  //通过其他线程改变共用变量breakflage，然后continue掉后续所有工作。
                RI_ij += 1;
                continue;
            }
            double WLT = WL_MIN + (I - 1) * (WL_MAX - WL_MIN) / (WL_NUM - 1);
            RI_setting(WLT, IMGHT, IMGWT_MIN, whichwave, Fieldtype);
            RI_result(WLT, IMGHT, IMGWT_MIN, whichwave, Fieldtype);
            pData3[(I - 1) * row + (J - 1)] = RIdata[0];
            RI_ij+=1;
            QApplication::processEvents();
        }
    }
    //textfile_RI.close();
    cout << "Relative Illuminationm finish!" << endl;
    mxSetField(m_RI, 0, "function", pMxArray3);
    TheSystem->SystemData->Fields->ConvertToFieldType(initialfieldtype);
    return m_RI;
}

void ZemaxProject::FFTPSF_Result(IAR_Ptr PSFWin_Results, int Displaysize, DOUBLE* input1,int I_wav,int J_ht) {
    int I = I_wav - 1; int J = J_ht - 1;
    for (int i = 0; i < PSFWin_Results->NumberOfDataGrids; i++) {
        IAR_DataGridPtr dataseries = PSFWin_Results->GetDataGrid(i);

        for (int x = dataseries->Nx - 1; x >=0 ; x--) {
            for (int y = 0; y < dataseries->Ny; y++) {
                //input1[y* (dataseries->Nx)+x+ij* (dataseries->Nx)*(dataseries->Ny)] = dataseries->ValueData->GetValueAt(x, y);
                //input1[y * (dataseries->Nx) + x + ij * (dataseries->Nx) * (dataseries->Ny)] = dataseries->ValueData->GetValueAt(PSFSize[Displaysize] - 1 - x, y);//从0开始计算的，所以到不了最大值
                //input1[y * (dataseries->Nx) + x + J * (dataseries->Nx) * (dataseries->Ny) + I* IMGHT_NUM*(dataseries->Nx) * (dataseries->Ny)] = dataseries->ValueData->GetValueAt(PSFSize[Displaysize]-1 -x, y);//从0开始计算的，所以到不了最大值
                input1[y * (dataseries->Nx) + x + J * (dataseries->Nx) * (dataseries->Ny) + I* IMGHT_NUM*(dataseries->Nx) * (dataseries->Ny)] = dataseries->ValueData->GetValueAt(x, y);//从0开始计算的，所以到不了最大值
            }
        }
    }
}

void ZemaxProject::FFTPSF_setting(double WLT, double IMGHT, double IMGWT, int whichwave, int Fieldtype, int Samplingsize,
    int Displaysize, int fftpsftype, double ImageDelta,bool isNormalize) {
    // 根据marco做基础设定
    sysWave->GetWavelength(whichwave)->Wavelength = WLT; //参考波长可根据需求设计添加
    TheSystem->SystemData->Fields->DeleteAllFields();
    TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)Fieldtype);
    TheSystem->SystemData->Fields->GetField(1)->X = IMGWT;
    TheSystem->SystemData->Fields->GetField(1)->Y = IMGHT;
    TheSystem->SystemData->Fields->SetVignetting();

    //根据Analyse-PSF-FFT设置条件
    IA_Ptr PSFWin = TheAnalyses->New_FftPsf();                                   //这里是分析FftPSF设置
    IAS_FftPsfPtr PSFSettings = PSFWin->GetSettings();                   //设置IAS_Fft
    PSFSettings->PutSampleSize(PsfSampling(Samplingsize));            //设置采样，例如为PsfSampling_PsfS_128x128
    PSFSettings->PutOutputSize(PsfSampling(Displaysize));         //设置显示，例如为64×64  ，就是为64×64矩阵PsfSampling_PsfS_256x256
    PSFSettings->Rotation = PsfRotation_CW0;
    PSFSettings->PutImageDelta(ImageDelta);
    if (whichwave == 0) {
        PSFSettings->Wavelength->UseAllWavelengths();
    }
    else {
        PSFSettings->Wavelength->SetWavelengthNumber(whichwave);
    }
    PSFSettings->Field->SetFieldNumber(1);
    PSFSettings->type = FftPsfType(fftpsftype);                             //FftPsfType_Linear
    PSFSettings->Surface->SetSurfaceNumber(TheLDE->NumberOfSurfaces - 1);
    PSFSettings->Normalize = isNormalize;                                   //设置是否归一化
    // Run Analysis                      进行分析
    PSFWin->ApplyAndWaitForCompletion();
    IAR_Ptr PSFWin_Results = PSFWin->GetResults();

    _bstr_t lenstitle = PSFWin_Results->MetaData->GetLensTitle();
    //cout << "NumberOfDataSeries:          " << PSFWin_Results->NumberOfDataGrids << endl;
    //filepath_FFTPSF =  (_bstr_t)outputFolder.c_str() + "\\" + file_name + "_ImageHeight_" + _bstr_t(IMGHT) + "_Wave" + _bstr_t(WLT) + "_fftPSF.txt";
    //textfile_FFTPSF.open(filepath_FFTPSF, ios::binary | ios::out | ios::trunc);
    FFTPSF_Result(PSFWin_Results, Displaysize);
    PSFWin->Close();

    //将PSF的size及sample信息记录到主txt中。
    fstream textfile_Baseparameters;
    textfile_Baseparameters.open(filepath_Baseparameters, ios::out|ios::app);
    textfile_Baseparameters << "psfSize= " << pow(2, PSFSettings->SampleSize - 1) * 32 << "% PSF ROW AND COL SIZE" << endl;
    textfile_Baseparameters << "psfSpacing= " << ImageDelta << "% GRID_SPACING:  The spacing between PSF samples (um)" << endl;
    //cout << "psfSize= " << pow(2, PSFSettings->SampleSize - 1) * 32 << "% PSF ROW AND COL SIZE" << endl;
    //cout << "psfSpacing= " << ImageDelta << "% GRID_SPACING:  The spacing between PSF samples (um)" << endl;
    TheSystem->SystemData->Fields->ConvertToFieldType(initialfieldtype);
}
mxArray* ZemaxProject::FFTPSFMultiple(int whichwave, int Fieldtype, int Samplingsize,
    int Displaysize, int fftpsftype, double ImageDelta,  bool isNormalize) {
    cout << "FFT PSF Processing..." << endl;
    
    IA_Ptr PSFWin = TheAnalyses->New_FftPsf();                                   //这里是分析FftPSF设置
    TheSystem->SystemData->Fields->DeleteAllFields();
    TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)Fieldtype);

    //直接打包成mat
    //// add field 'fftpsf'
    //mxArray* m_fftpsf = mxCreateStructMatrix(1, 1, 0, nullptr);
    mxAddField(m_fftpsf, "whichwave");
    mxSetField(m_fftpsf, 0, "whichwave", mxCreateString(to_string(whichwave).c_str()));

    mxAddField(m_fftpsf, "FieldType");
    mxSetField(m_fftpsf, 0, "FieldType", mxCreateString(fieldtype[Fieldtype].c_str()));

    mxAddField(m_fftpsf, "Samplingsize");
    mxSetField(m_fftpsf, 0, "Samplingsize", mxCreateString((to_string(PSFSize[Samplingsize]) + "x" + to_string(PSFSize[Samplingsize])).c_str()));

    mxAddField(m_fftpsf, "Displaysize");
    mxSetField(m_fftpsf, 0, "Displaysize", mxCreateString((to_string(PSFSize[Displaysize]) + "x" + to_string(PSFSize[Displaysize])).c_str()));

    mxAddField(m_fftpsf, "fftpsftype");
    mxSetField(m_fftpsf, 0, "fftpsftype", mxCreateString(FFTpsftype[fftpsftype].c_str()));

    mxAddField(m_fftpsf, "ImageDelta");
    mxSetField(m_fftpsf, 0, "ImageDelta", mxCreateDoubleScalar(ImageDelta));

    add_w_f_field(m_fftpsf);

    mxAddField(m_fftpsf, "function");
    mwSize ndim = 4; 
    mwSize dims[4] = { PSFSize[Displaysize],PSFSize[Displaysize], IMGHT_NUM, WL_NUM };
    mxArray* pMxArray4= mxCreateNumericArray(ndim, dims, mxDOUBLE_CLASS, mxREAL);
    DOUBLE* input1=(DOUBLE*)mxGetData(pMxArray4);
    /*step9:设置采样间距和采样点数，获取psf--FFT PSF*/
    FFTPSF_ij = 0;
    for (int I = 1; I <= WL_NUM; I++) {
        double WLT = WL_MIN + (I - 1) * (WL_MAX - WL_MIN) / (WL_NUM - 1);
        for (int J = 1; J <= IMGHT_NUM; J++) {
            if (breakflage) {  //通过其他线程改变共用变量breakflage，然后continue掉后续所有工作。
                FFTPSF_ij += 1;
                continue;
            }
            double IMGHT =-(IMGHT_MIN + (J - 1) * (IMGHT_MAX - IMGHT_MIN) / (IMGHT_NUM - 1));
            // 根据marco做基础设定
            TheSystem->SystemData->Fields->GetField(1)->X = IMGWT_MIN;
            TheSystem->SystemData->Fields->GetField(1)->Y = IMGHT;
            //TheSystem->SystemData->Fields->SetVignetting(); 
            TheSystem->SystemData->Fields->ClearVignetting();
            sysWave->GetWavelength(whichwave)->Wavelength = WLT; //参考波长可根据需求设计添加

            //根据Analyse-PSF-FFT设置条件
            IAS_FftPsfPtr PSFSettings = PSFWin->GetSettings();                   //设置IAS_Fft
            PSFSettings->PutSampleSize(PsfSampling(Samplingsize));            //设置采样，例如为PsfSampling_PsfS_128x128
            PSFSettings->PutOutputSize(PsfSampling(Displaysize));            //设置显示，例如为64×64  ，就是为64×64矩阵PsfSampling_PsfS_256x256
            PSFSettings->Rotation = PsfRotation_CW0;
            PSFSettings->PutImageDelta(ImageDelta);
            if (whichwave == 0) {
                PSFSettings->Wavelength->UseAllWavelengths();
            }
            else {
                PSFSettings->Wavelength->SetWavelengthNumber(whichwave);
            }
            PSFSettings->Field->SetFieldNumber(1);
            PSFSettings->type = FftPsfType(fftpsftype);                             //FftPsfType_Linear
            PSFSettings->Surface->SetSurfaceNumber(TheLDE->NumberOfSurfaces - 1);
            PSFSettings->Normalize = isNormalize;                                   //设置是否归一化
            // Run Analysis                      进行分析
            PSFWin->ApplyAndWaitForCompletion();

            IAR_Ptr PSFWin_Results = PSFWin->GetResults();
            //filepath_FFTPSF =  (_bstr_t)outputFolder.c_str() + "\\" + file_name +"_fftPSF_Wave" + _bstr_t(WLT) + "_ImageHeight_" + _bstr_t(IMGHT) + ".txt";
            //textfile_FFTPSF.open(filepath_FFTPSF, ios::binary | ios::out | ios::trunc);

            FFTPSF_Result(PSFWin_Results, Displaysize,input1, I,J);

            //textfile_FFTPSF.close();
            
            FFTPSF_ij += 1;
            QApplication::processEvents();

        }
    }

    PSFWin->Close();
    cout << "FFT PSF Finish!" << endl;
    TheSystem->SystemData->Fields->ConvertToFieldType(initialfieldtype);
    //real_data;
    mxSetField(m_fftpsf, 0, "function", pMxArray4);
    return m_fftpsf;
}

void ZemaxProject::HuygensPSF_Result(IAR_Ptr HuygensPSF_Results, int Displaysize, DOUBLE* input2, int I_wav, int J_ht) {
    int I = I_wav - 1; int J = J_ht - 1;
    for (int i = 0; i < HuygensPSF_Results->NumberOfDataGrids; i++) {
        IAR_DataGridPtr dataseries = HuygensPSF_Results->GetDataGrid(i);
        //cout << "Description:" << dataseries->Description << endl;
        //cout << "Nx is:" << dataseries->Nx << "  Ny is:" << dataseries->Ny << endl;

        for (int x = dataseries->Nx - 1; x >= 0; x--) {
            for (int y = 0; y < dataseries->Ny; y++) {
                //input[y * (dataseries->Nx) + x + ij * (dataseries->Nx) * (dataseries->Ny)] = (double)(dataseries->ValueData->GetValueAt(x, y));
                //input2[y * (dataseries->Nx) + x + ij * (dataseries->Nx) * (dataseries->Ny)] = dataseries->ValueData->GetValueAt(PSFSize[Displaysize]-1 - x, y);//从0开始计算的，所以到不了最大值
                //input2[y * (dataseries->Nx) + x + J * (dataseries->Nx) * (dataseries->Ny) + I * IMGHT_NUM * (dataseries->Nx) * (dataseries->Ny)] = dataseries->ValueData->GetValueAt(PSFSize[Displaysize] - 1 - x, y);//从0开始计算的，所以到不了最大值
                input2[y * (dataseries->Nx) + x + J * (dataseries->Nx) * (dataseries->Ny) + I * IMGHT_NUM * (dataseries->Nx) * (dataseries->Ny)] = dataseries->ValueData->GetValueAt(x, y);//反转
                
            }
            //textfile_HuygensPSF << endl;
        }
    }
}

void ZemaxProject::HuygensPSF_setting(double WLT, double IMGHT, double IMGWT, int whichwave, int Fieldtype, int Samplingsizetype,
    int displaysizetype, int HuygensPSFtype, double ImageDelta,  bool isNormalize) {
    // 根据marco做基础设定
    sysWave->GetWavelength(pwav)->Wavelength = WLT; //参考波长可根据需求设计添加
    TheSystem->SystemData->Fields->DeleteAllFields();
    TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)Fieldtype);
    TheSystem->SystemData->Fields->GetField(1)->X = IMGWT;
    TheSystem->SystemData->Fields->GetField(1)->Y = IMGHT;
    TheSystem->SystemData->Fields->SetVignetting();

    //根据Analyse-PSF-FFT设置条件
    IA_Ptr HuygensPSF = TheAnalyses->New_HuygensPsf();         //这里是分析FftPSF设置
    IAS_HuygensPsfPtr HuygensSetting = HuygensPSF->GetSettings();
    HuygensSetting->PupilSampleSize = SampleSizes(Samplingsizetype); //SampleSizes_S_128x128
    HuygensSetting->ImageSampleSize = SampleSizes(displaysizetype);  //SampleSizes_S_128x128
    //cout << "NumberOfFields:" << TheSystem->SystemData->Fields->NumberOfFields << "----" << "GetFieldY:" << TheSystem->SystemData->Fields->GetField(1)->Y << "----" << "wavelength:" << WLT << endl;
    HuygensSetting->Wavelength->SetWavelengthNumber(whichwave);
    HuygensSetting->Field->SetFieldNumber(1);
    HuygensSetting->PutImageDelta(ImageDelta);
    if (whichwave == 0) {
        HuygensSetting->Wavelength->UseAllWavelengths();
    }
    else {
        HuygensSetting->Wavelength->SetWavelengthNumber(pwav);
    }
    HuygensSetting->type = HuygensPsfTypes(HuygensPSFtype); //FftPsfType_Linear
    HuygensSetting->Normalize = isNormalize;            //设置是否归一化
    HuygensPSF->ApplyAndWaitForCompletion();     // Run Analysis
    IAR_Ptr HuygensPSF_Results = HuygensPSF->GetResults();  //get result
    _bstr_t lenstitle = HuygensPSF_Results->MetaData->GetLensTitle();

    HuygensPSF_Result(HuygensPSF_Results);

    //cout << "NumberOfDataSeries:          " << PSFWin_Results->NumberOfDataGrids << endl;
    //filepath_HuygensPSF =  (_bstr_t)outputFolder.c_str() + "\\" + file_name +"_ImageHeight_"+ _bstr_t(IMGHT) + "_Wave_" + _bstr_t(WLT) + "_HuygensPSF.txt";
    //textfile_HuygensPSF.open(filepath_HuygensPSF, ios::binary | ios::out | ios::trunc);
    TheSystem->SystemData->Fields->ConvertToFieldType(initialfieldtype);

}

mxArray* ZemaxProject::HuygensPSFMultiple(int whichwave, int Fieldtype, int Samplingsize,
    int Displaysize, int HuygensPSFtype, double ImageDelta,  bool isNormalize) {
    ///*step9:设置采样间距和采样点数，获取psf-Huygens psf*/
    cout << "HuygensPSF processing..." << endl;
    IA_Ptr HuygensPSF = TheAnalyses->New_HuygensPsf();         //这里是分析FftPSF设置

    //直接打包成mat
    //// add field 'fftpsf'
    //mxArray* m_huygenspsf = mxCreateStructMatrix(1, 1, 0, nullptr);
    mxAddField(m_huygenspsf, "whichwave");
    mxSetField(m_huygenspsf, 0, "whichwave", mxCreateString(to_string(whichwave).c_str()));

    mxAddField(m_huygenspsf, "FieldType");
    mxSetField(m_huygenspsf, 0, "FieldType", mxCreateString(fieldtype[Fieldtype].c_str()));

    mxAddField(m_huygenspsf, "Samplingsize");
    mxSetField(m_huygenspsf, 0, "Samplingsize", mxCreateString((to_string(PSFSize[Samplingsize]) + "x" + to_string(PSFSize[Samplingsize])).c_str()));

    mxAddField(m_huygenspsf, "Displaysize");
    mxSetField(m_huygenspsf, 0, "Displaysize", mxCreateString((to_string(PSFSize[Displaysize]) + "x" + to_string(PSFSize[Displaysize])).c_str()));

    mxAddField(m_huygenspsf, "fftpsftype");
    mxSetField(m_huygenspsf, 0, "fftpsftype", mxCreateString(Huygenspsftype[HuygensPSFtype].c_str()));

    mxAddField(m_huygenspsf, "ImageDelta");
    mxSetField(m_huygenspsf, 0, "ImageDelta", mxCreateDoubleScalar(ImageDelta));

    add_w_f_field(m_huygenspsf);

    mxAddField(m_huygenspsf, "function");
    mwSize ndim = 4;
    mwSize dims[4] = { PSFSize[Displaysize],PSFSize[Displaysize], IMGHT_NUM,WL_NUM };
    mxArray* pMxArray5 = mxCreateNumericArray(ndim, dims, mxDOUBLE_CLASS, mxREAL);
    DOUBLE* input2 = (DOUBLE*)mxGetData(pMxArray5);
    
    HuygensPSF_ij = 0;
    TheSystem->SystemData->Fields->DeleteAllFields();
    TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)Fieldtype);
    for (int I = 1; I <= WL_NUM; I++) {
        double WLT = WL_MIN + (I - 1) * (WL_MAX - WL_MIN) / (WL_NUM - 1);
        for (int J = 1; J <= IMGHT_NUM; J++) {
            if (breakflage) {  //通过其他线程改变共用变量breakflage，然后continue掉后续所有工作。
                HuygensPSF_ij += 1;
                continue;
            }
            double IMGHT = -(IMGHT_MIN + (J - 1) * (IMGHT_MAX - IMGHT_MIN) / (IMGHT_NUM - 1));
            // 根据marco做基础设定
            sysWave->GetWavelength(pwav)->Wavelength = WLT; //参考波长可根据需求设计添加
            TheSystem->SystemData->Fields->GetField(1)->X = IMGWT_MIN;
            TheSystem->SystemData->Fields->GetField(1)->Y = IMGHT;
            TheSystem->SystemData->Fields->SetVignetting();

            //根据Analyse-PSF-FFT设置条件
            IAS_HuygensPsfPtr HuygensSetting = HuygensPSF->GetSettings();
            HuygensSetting->PutPupilSampleSize(SampleSizes(Samplingsize)); //SampleSizes_S_128x128
            HuygensSetting->PutImageSampleSize(SampleSizes(Displaysize));  //SampleSizes_S_128x128
            HuygensSetting->Wavelength->SetWavelengthNumber(whichwave);
            HuygensSetting->Field->SetFieldNumber(1);
            HuygensSetting->PutImageDelta(ImageDelta);
            if (whichwave == 0) {
                HuygensSetting->Wavelength->UseAllWavelengths();
            }
            else {
                HuygensSetting->Wavelength->SetWavelengthNumber(pwav);
            }
            HuygensSetting->type = HuygensPsfTypes(HuygensPSFtype); //FftPsfType_Linear
            HuygensSetting->Normalize = isNormalize;            //设置是否归一化
            HuygensPSF->ApplyAndWaitForCompletion();     // Run Analysis
            IAR_Ptr HuygensPSF_Results = HuygensPSF->GetResults();  //get result

            //filepath_HuygensPSF =  (_bstr_t)outputFolder.c_str() + "\\" + file_name + "_HuygensPSF_Wave_" + _bstr_t(WLT) + "_ImageHeight_" + _bstr_t(IMGHT) + ".txt";
            //textfile_HuygensPSF.open(filepath_HuygensPSF, ios::binary | ios::out | ios::trunc);
            HuygensPSF_Result(HuygensPSF_Results, Displaysize, input2, I,J);
            //textfile_HuygensPSF.close();
            HuygensPSF_ij += 1;
            QApplication::processEvents();
        }
    }
    HuygensPSF->Close();
    cout << "HuygensPSF Finish!" << endl;
    TheSystem->SystemData->Fields->ConvertToFieldType(initialfieldtype);

    //real_data;
    mxSetField(m_huygenspsf, 0, "function", pMxArray5);
    return m_huygenspsf;
}

bool ZemaxProject::saveFile(_bstr_t savepath) {
    //储存新文件
    SaveFile = savepath;
    //if (_access(savepath, 0) == -1)
    //{
    //    // creates a new API directory
    //    CreateDirectory(_bstr_t( (_bstr_t)outputFolder.c_str() + "\\API"), NULL);
    //    CreateDirectory(_bstr_t( (_bstr_t)outputFolder.c_str() + "\\API\\CPP"), NULL);
    //};

    TheSystem->SaveAs(SaveFile);
    return true;
}

//***************完成项目后就关闭应用******************
void ZemaxProject::finishStandaloneApplication()
{
    // Note - TheApplication will close automatically when this application exits, so this isn't strictly necessary in most cases
    if (TheApplication != nullptr)
    {
        TheApplication->CloseApplication();
    }
}


//***************功能函数区******************
//-----------定义遇到的问题并报错----------------
bool ZemaxProject::handleError(std::string msg)
{
    cout << "error:::" << msg.c_str() << endl;
    throw new exception(msg.c_str());
    return -1;
}
bool ZemaxProject::logInfo(std::string msg)
{
    printf("%s", msg.c_str());
    return 0;
}
bool ZemaxProject::fileExists( wchar_t* name) {
    FILE* file;
    errno_t err = _wfopen_s(&file, name, L"r");
    if (err == 0) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}


//-----------定义切片---------------
vector<string>  ZemaxProject::split( string& src, string separate_character)
{
    vector<string> strs;
    int separate_characterLen = separate_character.size();//分割字符串的长度,这样就可以支持如“,,”多字符串的分隔符
    int lastPosition = 0, index = -1;
    while (-1 != (index = src.find(separate_character, lastPosition)))
    {
        strs.push_back(src.substr(lastPosition, index - lastPosition));
        lastPosition = index + separate_characterLen;
    }
    string lastString = src.substr(lastPosition);//截取最后一个分隔符后的内容
    if (!lastString.empty())
        strs.push_back(lastString);//如果最后一个分隔符后还有内容就入队
    return strs;
}
//-----------获取绝对路径-----------
void  ZemaxProject::getabspath(string folderpath, vector<string>& filespath, string filename) {
    //文件句柄 ,文件信息   
    long long   hFile = 0;
    struct _finddata_t* fileinfo = new _finddata_t;
    string pathPrefix;

    if ((hFile = _findfirst(pathPrefix.assign(folderpath).append("\\*").c_str(), fileinfo)) != -1) {
        do {
            //如果是子目录,递归查找子文件夹
            if ((fileinfo->attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo->name, ".") != 0 && strcmp(fileinfo->name, "..") != 0)
                    getabspath(pathPrefix.assign(folderpath).append("\\").append(fileinfo->name), filespath, filename);
            }
            //如果是文件，则加入查找结果
            else {
                if (string(fileinfo->name) == filename)
                    filespath.push_back(pathPrefix.assign(folderpath).append("\\").append(fileinfo->name));
            }
        } while (_findnext(hFile, fileinfo) == 0);
        //通过句柄关闭当前目录查找
        _findclose(hFile);
    }
}

//将所有的Mat写到这里
void ZemaxProject::saveOIToMatFile(vector<ANYData> params_setting)
///在这里进行设计，将必要的字段全部添加在这里。
{
    unsigned int WL_NUM = params_setting[0].uival;
    double WL_MIN = params_setting[1].dval;
    double WL_MAX = params_setting[2].dval;
    unsigned int IMGHT_NUM = params_setting[3].uival;
    double IMGHT_MIN = params_setting[4].dval;
    double IMGHT_MAX = params_setting[5].dval;
    // check and create output folder
    m_rayTrace = mxCreateStructMatrix(1, 1, 0, nullptr);
    m_Distorition = mxCreateStructMatrix(1, 1, 0, nullptr);
    m_CRA = mxCreateStructMatrix(1, 1, 0, nullptr);
    m_RI = mxCreateStructMatrix(1, 1, 0, nullptr);
    m_fftpsf = mxCreateStructMatrix(1, 1, 0, nullptr);
    m_huygenspsf = mxCreateStructMatrix(1, 1, 0, nullptr);

    //string outFolder = "./output/";
    if (0 != _access(outputFolder.c_str(), 0))
    {
        // if this folder not exist, create a new one.

        if (createDirectory(outputFolder))   // return 0, if successfully created
        {
            fprintf(stderr, "error: cannot create folder '%s', ", outputFolder.c_str());
            fprintf(stderr, "in File '%s', line %d. \n", __FILE__, __LINE__);
            exit(1);
        }
    }
    // open out file
    string outFileFull = outputFolder + outFileName + ".mat";
    out_File = matOpen(outFileFull.c_str(), "w7.3");
    if (out_File == nullptr)
    {
        fprintf(stderr, "error: cannot open out file %s, ", outFileFull.c_str());
        fprintf(stderr, "in File '%s', line %d. \n", __FILE__, __LINE__);
    }
    // create oi struct  创建结构体
    oiStruct = mxCreateStructMatrix(1, 1, 0, nullptr);
    // add field 'type'  给结构体设置字段
    mxAddField(oiStruct, "type");
    mxArray* projectpath = mxCreateString("optics"); //给结构体每个字段填写值
    mxSetField(oiStruct, 0, "type", projectpath);

    // add field 'projectpath'  给结构体设置字段
    mxAddField(oiStruct, "model");
    mxArray* model = mxCreateString("raytrace");
    mxSetField(oiStruct, 0, "model", model);

    // add field 'fNumber'
    mxAddField(oiStruct, "fNumber");

    // add field 'focalLength'
    mxAddField(oiStruct, "focalLength");

    // add field 'transmittance'
    m_transmittance = mxCreateStructMatrix(1, 1, 0, nullptr);
    if (m_transmittance != nullptr)
    {
        mxAddField(oiStruct, "transmittance");
        mxSetField(oiStruct, 0, "transmittance", m_transmittance);
    }
    // add field 'vignetting'  给结构体设置字段
    mxAddField(oiStruct, "vignetting");
    mxArray* m_vignetting = mxCreateDoubleScalar(1);
    mxSetField(oiStruct, 0, "vignetting", m_vignetting);

    mxAddField(oiStruct, "rayTrace");
    mxSetField(oiStruct, 0, "rayTrace", m_rayTrace);

    // transmittance 里add field 'imageheight''wavelength'。。。
    if (WL_NUM && IMGHT_NUM)
    {
        //具体的数据-Wavelength
        mxAddField(m_transmittance, "wave");
        mxArray* pMxArray1;
        pMxArray1 = mxCreateNumericMatrix(WL_NUM, 1, mxDOUBLE_CLASS, mxREAL);
        double* pData1 = mxGetPr(pMxArray1);
        for (int I = 1; I <= WL_NUM; I++) {
            double WLT = WL_MIN + (I - 1) * (WL_MAX - WL_MIN) / (WL_NUM - 1);
            pData1[I - 1] = WLT;
        }
        mxSetField(m_transmittance, 0, "wave", pMxArray1);

        //-------------------------------------------------------------------------------
        //mxAddField(m_transmittance, "height");
        //mxArray* pMxArray2;
        //pMxArray2 = mxCreateNumericMatrix(IMGHT_NUM, 1, mxDOUBLE_CLASS, mxREAL);
        //double* pData2 = mxGetPr(pMxArray2);
        //for (int J = 1; J <= WL_NUM; J++) {
        //    double IMGHT = IMGHT_MIN + (J - 1) * (IMGHT_MAX - IMGHT_MIN) / (IMGHT_NUM - 1);
        //    pData2[J - 1] = IMGHT;
        //}
        //mxSetField(m_transmittance, 0, "height", pMxArray2);
    }
}

void ZemaxProject::closemat() {
    //mxDestroyArray(m_transmittance); mxDestroyArray(m_rayTrace);
    //mxDestroyArray(m_Distorition); mxDestroyArray(m_CRA);
    //mxDestroyArray(m_RI); mxDestroyArray(m_fftpsf);
    //mxDestroyArray(m_huygenspsf);
    mxDestroyArray(oiStruct);
    matClose(out_File);
}