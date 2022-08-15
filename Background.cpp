#include "stdafx.h"
#include "Background.h"
#include <iostream>
#include <algorithm>
# include <mat.h>
#include <atlstr.h>

void backStage::backgroundProcessing(int argc, char* argv[]) {
    cout << "---------------$$$$$-------------" << endl;
    //分三部分传入和获取参数，1）文件路径波长像高；2）MultipleTask运行选项及相关设定；3）其他必要设置，如rayaming。
    //参数列表：：
    //string cmdline = "background \"C:\\Users\\admin\\Documents\\Zemax\\Samples\\Sequential\\Objectives\\Cooke 40 degree field.zmx\" 60 0.1 0.9 60 0.0 20.00 0 0.0 0.0 1 0 0 0 0";
    //unsigned int WL_NUM = 31;    double WL_MIN = 0.400;    double WL_MAX = 0.700;
    //unsigned int IMGHT_NUM = 91; double IMGHT_MIN = 0.0; double IMGHT_MAX = 20.0;
    //unsigned int IMGWT_NUM = 0; double IMGWT_MIN = 0.0; double IMGWT_MAX = 0.0;
    bool checkDistortionMultiple, checkChiefRayAngleMultiple, checkRelativeIlluminationMultiple,
        checkFFTPSFMultiple, checkHuygensPSFMultiple;
    int Dis_whichwave, Dis_Fieldtypeindex, Dis_Distortiontype, Dis_Scantype;
    int CRA_whichwave, CRA_direction;
    int RI_whichwave, RI_direction;
    int FFT_whichwave, FFT_Fieldtypeindex, FFT_Scantype, FFT_sampling, FFT_display, FFT_type, FFT_normalize;double FFT_imagedelta; 
    int Huygens_whichwave, Huygens_Fieldtypeindex, Huygens_Scantype, Huygens_sampling, Huygens_display, Huygens_type,Huygens_normalize;double  Huygens_imagedelta;
    int rayaming;
    //1）文件路径波长像高
    string PathName = argv[1];
    pathConvert_Single2Double(PathName);
    unsigned int wlnum = atoi(argv[2]);
    double wlmin = stod(argv[3]);
    double wlmax = stod(argv[4]);
    unsigned int imghtnum = stoi(argv[5]);
    double imghtmin = stod(argv[6]);
    double imghtmax = stod(argv[7]);
    unsigned int imgwtnum = stoi(argv[8]);
    double imgwtmin = stod(argv[9]);
    double imgwtmax = stod(argv[10]);
    //2）MultipleTask运行选项及相关设定
    string argv11 = argv[11]; string argv12 = argv[12]; string argv13 = argv[13]; string argv14 = argv[14]; string argv15 = argv[15];
    vector<string> split11 = Projectback.split(argv11, "_");
    checkDistortionMultiple = stoi(split11[0]); Dis_whichwave= stoi(split11[1]); Dis_Fieldtypeindex=stoi(split11[2]); Dis_Distortiontype=stoi(split11[3]); Dis_Scantype=stoi(split11[4]);
    vector<string> split12 = Projectback.split(argv12, "_");
    checkChiefRayAngleMultiple = stoi(split12[0]); CRA_whichwave = stoi(split12[1]); CRA_direction = stoi(split12[2]); 
    vector<string> split13 = Projectback.split(argv13, "_");
    checkRelativeIlluminationMultiple = stoi(split13[0]); RI_whichwave = stoi(split13[1]); RI_direction = stoi(split13[2]);
    vector<string> split14 = Projectback.split(argv14, "_");
    checkFFTPSFMultiple = stoi(split14[0]); FFT_whichwave= stoi(split14[1]), FFT_Fieldtypeindex= stoi(split14[2]), FFT_Scantype= stoi(split14[3]), FFT_sampling = stoi(split14[4]), FFT_display = stoi(split14[5]), FFT_type = stoi(split14[6]), FFT_imagedelta = stod(split14[7]), FFT_normalize = stoi(split14[8]);
    vector<string> split15 = Projectback.split(argv15, "_");
    checkHuygensPSFMultiple = stoi(split15[0]); Huygens_whichwave= stoi(split15[1]), Huygens_Fieldtypeindex= stoi(split15[2]), Huygens_Scantype= stoi(split15[3]), Huygens_sampling = stoi(split15[4]), Huygens_display = stoi(split15[5]), Huygens_type = stoi(split15[6]), Huygens_imagedelta = stod(split15[7]), Huygens_normalize = stoi(split15[8]);
    //3）其他必要设置，如rayaming。
    rayaming= stoi(argv[16]);

    cout << "PathName::" << PathName << endl;
    cout << wlnum << "--" << wlmin <<"--" << wlmax <<"--" << imghtnum <<"--" << imghtmin <<"--" << imghtmax <<"--" << imgwtnum <<"--" << imgwtmin <<"--" << imgwtmax <<"--" << endl;
    cout << argv11 <<"--"<< argv12<<"--"<< argv13<<"--"<< argv14<<"--"<< argv15<< "--" << rayaming<<endl;
    cout << "split11::" << checkDistortionMultiple << "---" << Dis_whichwave << "---" << Dis_Fieldtypeindex << "---" << Dis_Distortiontype << endl;
    cout << "split12::" << checkChiefRayAngleMultiple << "---" << CRA_whichwave << "---" << CRA_direction << endl;
    cout << "split13::" << checkRelativeIlluminationMultiple << "---" << RI_whichwave << "---" << RI_direction << endl;
    cout << "split14::" << checkFFTPSFMultiple << "---" << FFT_whichwave << "---" << FFT_Fieldtypeindex << "---" << FFT_Scantype <<"---"  << FFT_sampling << "---" << FFT_display <<"---" << FFT_type << "---" << FFT_imagedelta <<"---" << FFT_normalize<< endl;
    cout << "split15::" << checkHuygensPSFMultiple << "---" << Huygens_whichwave << "---" << Huygens_Fieldtypeindex << "---" << Huygens_Scantype << "---" << Huygens_sampling << "---" << Huygens_display << "---" << Huygens_type << "---" << Huygens_imagedelta << "---" << Huygens_normalize << endl;

    unsigned int wl_num = Projectback.set_WL_NUM(wlnum);
    double wl_min = Projectback.set_WL_MIN(wlmin);
    double wl_max = Projectback.set_WL_MAX(wlmax);
    unsigned int imght_num = Projectback.set_IMGHT_NUM(imghtnum);
    double imght_min = Projectback.set_IMGHT_MIN(imghtmin);
    double imght_max = Projectback.set_IMGHT_MAX(imghtmax);
    unsigned int imgwt_num = Projectback.set_IMGWT_NUM(imgwtnum);
    double imgwt_min = Projectback.set_IMGWT_MIN(imgwtmin);
    double imgwt_max = Projectback.set_IMGWT_MAX(imgwtmax);
    //基础设定
    Projectback.createApplication();
    cout << "createApplication is complished" << endl;
    Projectback.inputFile = PathName.c_str();
    Projectback.loadmyFile(PathName.c_str());
    Projectback.basicSetting();
    Projectback.propertySetting();
    Projectback.TheSystem->SystemData->RayAiming->PutRayAiming((RayAimingMethod)rayaming);
    Projectback.TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)Dis_Fieldtypeindex);
    //以“/”和“.”为分隔符获取文件名字
    vector<string> pnsplit = Projectback.split(PathName, "/");
    vector<string> nsplit = Projectback.split(pnsplit.back(), ".");
    transform(nsplit.back().begin(), nsplit.back().end(), nsplit.back().begin(), ::tolower);
    Projectback.file_name = nsplit.front().c_str();
    Projectback.getLensProperties();
    cout << "Projectback.file_name:::" << Projectback.file_name << endl;
    vector<ANYData> params_setting = Projectback.getYourSetting();

    time_t startdis, enddis, startcra, endcra, startri, endri, startfft, endfft, starthuygens, endhuygens;       // 计时
    double costdis = 0, costcra = 0, costri = 0, costfft = 0, costhuygens = 0;
    //	//将所有数据打包
    saveOIToMatFile(params_setting);
    //5项任务
    if (checkDistortionMultiple) {
        startdis = clock();
        //用户可设定的参数：int whichwave = 1, int Fieldtype = 2, int Distortiontype = 0, int Scantype = 0
        mxArray* mydistortion = Projectback.DistortionMultiple(Dis_whichwave, Dis_Fieldtypeindex, Dis_Distortiontype, Dis_Scantype);
        // add field 'Distorition'
        mxAddField(oiStruct, "Distorition");
        mxSetField(oiStruct, 0, "Distorition", mydistortion);
        enddis = clock();
        costdis = (double)(enddis - startdis) / CLOCKS_PER_SEC;
    }
    if (checkChiefRayAngleMultiple) {
        startcra = clock();
        //用户可设定的参数：int whichwave = 1, int Fieldtype = 2, int Distortiontype = 0, int Scantype = 0
        mxArray* mycra = Projectback.ChiefRayAngleMultiple(Projectback.pwav, Dis_Fieldtypeindex);
        // add field 'CRA'
        mxAddField(oiStruct, "CRA");
        mxSetField(oiStruct, 0, "CRA", mycra);
        endcra = clock();
        costcra = (double)(endcra - startcra) / CLOCKS_PER_SEC;
    }
    if (checkRelativeIlluminationMultiple) {
        startri = clock();
        //用户可设定的参数：int whichwave = 1, int Fieldtype = 2, int Distortiontype = 0, int Scantype = 0
        mxArray* ri = Projectback.RIMultiple(Projectback.pwav, Dis_Fieldtypeindex);
        // add field 'RI'
        mxAddField(oiStruct, "RI");
        mxSetField(oiStruct, 0, "RI", ri);
        endri = clock();
        costri = (double)(endri - startri) / CLOCKS_PER_SEC;
    }
    if (checkFFTPSFMultiple) {
        startfft = clock();
        //用户可设定的参数：int whichwave, int Fieldtype, int Samplingsizetype,int Displaysizetype, int fftpsftype, double ImageDelta, bool isNormalize
        mxArray* fftpsf = Projectback.FFTPSFMultiple(FFT_whichwave, FFT_Fieldtypeindex, FFT_sampling, FFT_display, FFT_type, FFT_imagedelta, FFT_normalize);
        // add field 'fftpsf'
        mxAddField(oiStruct, "FFTPSF");
        mxSetField(oiStruct, 0, "FFTPSF", fftpsf);
        endfft = clock();
        costfft = (double)(endfft - startfft) / CLOCKS_PER_SEC;
    }
    if (checkHuygensPSFMultiple) {
        starthuygens = clock();
        //用户可设定的参数：int whichwave, int Fieldtype, int Samplingsizetype,int displaysizetype, double ImageDelta, int HuygensPSFtype, bool isNormalize
        mxArray* huygenspsf = Projectback.HuygensPSFMultiple(Huygens_whichwave, Huygens_Fieldtypeindex, Huygens_sampling, Huygens_display, Huygens_type, Huygens_imagedelta, Huygens_normalize);
        // add field 'fftpsf'
        mxAddField(oiStruct, "Huygens");
        mxSetField(oiStruct, 0, "Huygens", huygenspsf);
        endhuygens = clock();
        costhuygens = (double)(endhuygens - starthuygens) / CLOCKS_PER_SEC;
    }
    double totalcost;
    totalcost = costdis + costcra + costri + costfft + costhuygens;
    // write to file
    matPutVariable(out_File, outFileName.c_str(), oiStruct);
    closemat();

    CString msg;
    msg.Format(_T("总耗时:%lf\n"), totalcost);
    MessageBox(0, msg, _T("状态"), MB_OK | MB_ICONWARNING);
}

//单斜杠转双斜杠
void backStage::pathConvert_Single2Double(string& s) {
    string::size_type pos = 0;
    while ((pos = s.find('\\', pos)) != string::npos) {
        s.insert(pos, "\\");
        pos = pos + 2;
    }
}
