#include "stdafx.h"
#include "zemaxqt.h"
#include <QtWidgets/qspinbox.h>
//#include "zemaxqt_subweights.h"


//自定义SLOT-main weight里
//for close any Tab
void zemaxqt::closeTabSlot(int index)
{
	if (index != 0) {
		ui->tabWidget->removeTab(index);
	}
	if (index == reporttabindex) {
		ui->Reports->setEnabled(true);
	};
	if (index == actionDistoritiontabindex) {
		ui->actionDistorition->setEnabled(true);
	};
}

void zemaxqt::WavelengthChangeSlot() {
	WavelengthNumber = spinBoxWavelengthNumber->value();
	WLTchange = Project1.sysWave->GetWavelength(WavelengthNumber)->Wavelength;
	lineWaveLengthValue->setText(QString::fromStdString(to_string(WLTchange)));
}

void zemaxqt::ImageHeightWidthChangeSlot() {
	fieldtypecurrentIndex = ComboBoxFieldType->currentIndex();
	Project1.TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)fieldtypecurrentIndex);
	fieldY = Project1.TheSystem->SystemData->Fields->GetField(Project1.SystemImageheightMaxIndex)->Y;
	fieldX = Project1.TheSystem->SystemData->Fields->GetField(Project1.SystemImageheightMaxIndex)->X;
	lineEditlabelImageHeight->setText(QString::fromStdString(to_string(fieldY)));
	lineEditlabelImageWidth->setText(QString::fromStdString(to_string(fieldX)));
}

//for buildDistoritionTab
void zemaxqt::DistortionChangeSlot() {
	WavelengthNumber = spinBoxWavelengthNumber->value();
	ImageHeightchange = lineEditlabelImageHeight->text();
	ImageWidthchange = lineEditlabelImageWidth->text();
	fieldtypecurrentIndex = ComboBoxFieldType->currentIndex();
	ScanTypecurrentIndex = ComboBoxScanType->currentIndex();

	double WLTchg = Project1.sysWave->GetWavelength(WavelengthNumber)->Wavelength;
	double IMGHTchg = ImageHeightchange.toDouble();
	double IMGWTchg = ImageWidthchange.toDouble(); int whichwavechg = WavelengthNumber;
	int Fieldtypechg = fieldtypecurrentIndex; int Distortiontypechg = 0; int Scantypechg = ScanTypecurrentIndex;
	Project1.Distorition_setting(WLTchg, IMGHTchg, IMGWTchg, whichwavechg, Fieldtypechg, Distortiontypechg, Scantypechg);

	textEditResult->append(QString::fromStdString(to_string(Project1.distoritiondata[0])) + ":");
	textEditResult->append(QString::fromStdString(to_string(Project1.distoritiondata[1])));
}
void zemaxqt::FieldHTNumberverify() {
	int HTNumber = (ui->lineEditFieldHTNumber->text()).toInt();
	if (HTNumber < 0 || HTNumber > 120) {
		ui->lineEditFieldHTNumber->setText(QString::fromStdString(to_string(90)));
		ui->textEdit->clear();
		ui->textEdit->setText("Image Height Number Value Range:1-120.");
	}
}

void zemaxqt::FieldHTMaxverify() {
	double max = (ui->lineEditFieldHTMax->text()).toDouble();
	double min = (ui->lineEditFieldHTMin->text()).toDouble();

	if (max < min) {
		ui->lineEditFieldHTMax->setText(QString::fromStdString(to_string(initialfieldYmaxvalue)));
		ui->textEdit->clear();
		ui->textEdit->setText("FieldMax Must greater than FieldMin.");
	}
	if (max > 40.0) {
		ui->lineEditFieldHTMax->setText(QString::fromStdString(to_string(initialfieldYmaxvalue)));
		ui->textEdit->clear();
		ui->textEdit->setText("Field Value Range:0-40.");
	}
}

void zemaxqt::FieldHTMinverify() {
	double max = (ui->lineEditFieldHTMax->text()).toDouble();
	double min = (ui->lineEditFieldHTMin->text()).toDouble();

	if (max < min) {
		ui->lineEditFieldHTMin->setText(QString::fromStdString(to_string(0.0)));
		ui->textEdit->clear();
		ui->textEdit->setText("FieldMax Must greater than FieldMin.");
	}
	if (min > 40.0) {
		ui->lineEditFieldHTMin->setText(QString::fromStdString(to_string(0.0)));
		ui->textEdit->clear();
		ui->textEdit->setText("Field Value Range:0-40.");
	}
}
void zemaxqt::AllFieldtypeverifyandFieldHTMaxChange() {
	int index = ui->comboBoxAllFieldtype->currentIndex();
	ui->comboBoxFieldtype->setCurrentIndex(index);
	ui->comboBoxFieldtype_4->setCurrentIndex(index);
	ui->comboBoxFieldtype_5->setCurrentIndex(index);
	//同时根据Fieldtype的改变转换一下FieldHTMax
	Project1.TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)index);
	double changedfieldYmaxvalue = Project1.TheSystem->SystemData->Fields->GetField(Project1.max_num_field)->Y;
	ui->lineEditFieldHTMax->setText(QString::fromStdString(to_string(changedfieldYmaxvalue)));
	cout << "initialfieldtype::" << Project1.initialfieldtype << endl;
	Project1.TheSystem->SystemData->Fields->ConvertToFieldType(Project1.initialfieldtype);
}

void zemaxqt::WavelengthNumberverify() {
	int WavelengthNumber = (ui->lineEditWavelengthNumber->text()).toInt();
	if (WavelengthNumber < 0 || WavelengthNumber > 120) {
		ui->lineEditWavelengthNumber->setText(QString::fromStdString(to_string(31)));
		ui->textEdit->clear();
		ui->textEdit->setText("Wavelength Number Value Range:1-120.");
	}
}
void zemaxqt::WavelengthMaxverify() {
	double max = ui->lineEditWavelengthMax->text().toDouble();
	double min = ui->lineEditWavelengthMin->text().toDouble();

	if (max / 1000 < min / 1000) {
		ui->lineEditWavelengthMax->setText(QString::fromStdString(to_string(700)));
		ui->textEdit->clear();
		ui->textEdit->setText("WaveMax Must greater than WaveMin.");
	}
	if (max / 1000 > 0.9) {
		ui->lineEditWavelengthMax->setText(QString::fromStdString(to_string(700)));
		ui->textEdit->clear();
		ui->textEdit->setText("Wavelength Value Range:200nm-900nm");
	}
}

void zemaxqt::WavelengthMinverify() {
	double max= ui->lineEditWavelengthMax->text().toDouble();
	double min = ui->lineEditWavelengthMin->text().toDouble();

	if (max / 1000 < min / 1000) {
		ui->lineEditWavelengthMin->setText(QString::fromStdString(to_string(400)));
		ui->textEdit->clear();
		ui->textEdit->setText("WaveMax Must greater than WaveMin.");
	}
	if (min / 1000 < 0.2|| min / 1000>0.9) {
		ui->lineEditWavelengthMin->setText(QString::fromStdString(to_string(400)));
		ui->textEdit->clear();
		ui->textEdit->setText("Wavelength Value Range:200nm-900nm");
	}
}

void zemaxqt::AllSamplingsizeverify() {
	int index = ui->comboBoxAllSampling->currentIndex();
	ui->comboBoxSampling_4->setCurrentIndex(index);
	ui->comboBoxSampling_5->setCurrentIndex(index);
}
void zemaxqt::AllDisplaysizeverify() {
	int index = ui->comboBoxAllDisplay->currentIndex();
	ui->comboBoxDisplay_4->setCurrentIndex(index);
	ui->comboBoxDisplay_5->setCurrentIndex(index);
}

void zemaxqt::AllImageDeltaverify() {
	double number = (ui->lineEditAllImageDelta->text()).toDouble();
	ui->labelImageDelta_4->setText(QString::fromStdString(to_string(number)));
	ui->labelImageDelta_5->setText(QString::fromStdString(to_string(number)));
}


void zemaxqt::dwPidchangeSlot(int dwPid) {
	if (dwPid == -1) {
		ui->pushButtonCanceling->setEnabled(false);
		ui->textEdit->clear();
		ui->textEdit->setText("Program Running Finished!");
		ui->pushButtonRunning->setEnabled(true);
	}
}


void zemaxqt::TasksScheduleSlot() {
	vector<ANYData> param = Project1.getYourSetting();
	unsigned int WL_NUM = param[0].uival;
	double WL_MIN = param[1].dval;
	double WL_MAX = param[2].dval;
	unsigned int IMGHT_NUM = param[3].uival;
	double IMGHT_MIN = param[4].dval;
	double IMGHT_MAX = param[5].dval;
	//设定显示逻辑，条件：设置好百分比及进度条。1.每隔一秒刷新一次；2.任务完成一个即刷新textEdit；3.每更新一个ij数字即刷新textEdit
	//int HTNumber = (ui->lineEditFieldHTNumber->text()).toInt();
	//int WavelengthNumber = (ui->lineEditWavelengthNumber->text()).toInt();
	int HTNumber = IMGHT_NUM;
	int WavelengthNumber = WL_NUM;
	int totalnumber = HTNumber * WavelengthNumber;
	//Distorition的进度
	int process_Distorition_ij = Project1.Distorition_ij;
	int Distorition_normal100 = (double(process_Distorition_ij) / double(totalnumber)) * 50;
	//CRA的进度
	int process_CRA_ij = Project1.CRA_ij;
	int CRA_normal100 = (double(process_CRA_ij) / double(totalnumber)) * 50;
	//RI的进度
	int process_RI_ij = Project1.RI_ij;
	int RI_normal100 = (double(process_RI_ij) / double(totalnumber)) * 50;
	//FFTPSF的进度
	int process_FFTPSF_ij = Project1.FFTPSF_ij;
	int FFTPSF_normal100 = (double(process_FFTPSF_ij) / double(totalnumber))*50;
	//HuygensPSF的进度
	int process_HuygensPSF_ij = Project1.HuygensPSF_ij;
	int HuygensPSF_normal100 = (double(process_HuygensPSF_ij) / double(totalnumber)) * 50;
	if (checkDistortionMultipleflag ==1)	taskScheduleappendix(process_Distorition_ij, totalnumber, Distorition_normal100, "Distortion:");
	if (checkChiefRayAngleMultipleflag ==1)taskScheduleappendix(process_CRA_ij, totalnumber, CRA_normal100, "CRA:");
	if (checkRelativeIlluminationMultipleflag ==1)taskScheduleappendix(process_RI_ij, totalnumber, RI_normal100, "RI:");
	if (checkFFTPSFMultipleflag ==1)taskScheduleappendix(process_FFTPSF_ij, totalnumber, FFTPSF_normal100, "FFTPSF:");
	if (checkHuygensPSFMultipleflag ==1)taskScheduleappendix(process_HuygensPSF_ij, totalnumber, HuygensPSF_normal100, "HuygensPSF:");
}

void zemaxqt::taskScheduleappendix(int a_process_ij,int a_totalnumber,int a_normal100,char* a_flag) {

	if (a_process_ij != a_totalnumber)
	{
		ui->textEdit->clear();
		for (int i = 0; i <= a_normal100; i++) {
			ui->textEdit->insertPlainText("=");
		}
		ui->textEdit->insertPlainText(">");
		ui->textEdit->insertPlainText(
			a_flag +
			QString::number(a_process_ij)
			+ "/" + QString::number(a_totalnumber)
		);

	}
	else if (a_process_ij == a_totalnumber)
	{
		ui->textEdit->clear();
		for (int i = 0; i <= a_normal100; i++) {
			ui->textEdit->insertPlainText("=");
		}
		ui->textEdit->insertPlainText(">");
		ui->textEdit->insertPlainText(
			a_flag +
			QString::number(a_totalnumber)
			+ "/" + QString::number(a_totalnumber)
		);
	}
}