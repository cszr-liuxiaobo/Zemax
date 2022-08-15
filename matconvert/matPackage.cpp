//#include <string>
//#include <mat.h>
//#include <math.h>
//#include <iostream>
//#include <stdio.h>
//#include <io.h>
//#include <direct.h>
//#include <vector>
//#include "matPackage.h"
//
//using namespace std;
//
//
//void saveMat::saveOIToMatFile(vector<ANYData> params_setting)
/////在这里进行设计，将必要的字段全部添加在这里。
//{
//    unsigned int WL_NUM = params_setting[0].uival;
//    double WL_MIN = params_setting[1].dval;
//    double WL_MAX = params_setting[2].dval;
//    unsigned int IMGHT_NUM = params_setting[3].uival;
//    double IMGHT_MIN = params_setting[4].dval;
//    double IMGHT_MAX = params_setting[5].dval;
//    // check and create output folder
//
//    string outFolder = "./output/";
//    if (0 != _access(outFolder.c_str(), 0))
//    {
//        // if this folder not exist, create a new one.
//        if (_mkdir(outFolder.c_str()))   // return 0, if successfully created
//        {
//            fprintf(stderr, "error: cannot create folder '%s', ", outFolder.c_str());
//            fprintf(stderr, "in File '%s', line %d. \n", __FILE__, __LINE__);
//            exit(1);
//        }
//    }
//    // open out file
//    string outFileFull = outFolder + outFileName + ".mat";
//    out_File = matOpen(outFileFull.c_str(), "w7.3");
//    if (out_File == nullptr)
//    {
//        fprintf(stderr, "error: cannot open out file %s, ", outFileFull.c_str());
//        fprintf(stderr, "in File '%s', line %d. \n", __FILE__, __LINE__);
//    }
//    // create oi struct  创建结构体
//    oiStruct = mxCreateStructMatrix(1, 1, 0, nullptr);
//    // add field 'type'  给结构体设置字段
//    mxAddField(oiStruct, "type");
//    mxArray* projectpath = mxCreateString("optics"); //给结构体每个字段填写值
//    mxSetField(oiStruct, 0, "type", projectpath);
//
//    // add field 'projectpath'  给结构体设置字段
//    mxAddField(oiStruct, "model");
//    mxArray* model = mxCreateString("raytrace");
//    mxSetField(oiStruct, 0, "model", model);
//
//    // add field 'fNumber'
//    mxAddField(oiStruct, "fNumber");
//
//    // add field 'focalLength'
//    mxAddField(oiStruct, "focalLength");
//
//    // add field 'transmittance'
//    m_transmittance = mxCreateStructMatrix(1, 1, 0, nullptr);
//    if (m_transmittance != nullptr)
//    {
//        mxAddField(oiStruct, "transmittance");
//        mxSetField(oiStruct, 0, "transmittance", m_transmittance);
//    }
//    // add field 'vignetting'  给结构体设置字段
//    mxAddField(oiStruct, "vignetting");
//    mxArray* m_vignetting = mxCreateDoubleScalar(1);
//    mxSetField(oiStruct, 0, "vignetting", m_vignetting);
//
//    mxAddField(oiStruct, "rayTrace");
//    mxSetField(oiStruct, 0, "rayTrace", m_rayTrace);
//
//    // transmittance 里add field 'imageheight''wavelength'。。。
//    if (WL_NUM&& IMGHT_NUM)
//    {
//        //具体的数据-Wavelength
//        mxAddField(m_transmittance, "wave");
//        mxArray* pMxArray1;
//        pMxArray1 = mxCreateNumericMatrix(WL_NUM, 1, mxDOUBLE_CLASS, mxREAL);
//        double* pData1 = mxGetPr(pMxArray1);
//        for (int I = 1; I <= WL_NUM; I++) {
//            double WLT = WL_MIN + (I - 1) * (WL_MAX - WL_MIN) / (WL_NUM - 1);
//            pData1[I-1] = WLT;
//        }
//        mxSetField(m_transmittance, 0, "wave", pMxArray1);
//
//        //-------------------------------------------------------------------------------
//        //mxAddField(m_transmittance, "height");
//        //mxArray* pMxArray2;
//        //pMxArray2 = mxCreateNumericMatrix(IMGHT_NUM, 1, mxDOUBLE_CLASS, mxREAL);
//        //double* pData2 = mxGetPr(pMxArray2);
//        //for (int J = 1; J <= IMGHT_NUM; J++) {
//        //    double IMGHT = IMGHT_MIN + (J - 1) * (IMGHT_MAX - IMGHT_MIN) / (IMGHT_NUM - 1);
//        //    pData2[J - 1] = IMGHT;
//        //}
//        //mxSetField(m_transmittance, 0, "height", pMxArray2);
//    }
//}
//
//void saveMat::closemat() {
//    matClose(out_File);
//    mxDestroyArray(oiStruct);
//}
