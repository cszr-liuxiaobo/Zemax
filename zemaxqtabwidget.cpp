#include "stdafx.h"
#include <iostream>
#include <QtCore/qstring.h>
#include <QTSql/QSqlQuery>
#include <ActiveQt/activeqtversion.h>
#include <QtWidgets/QFileDialog>
#include <QtCore/QDebug>
#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QComboBox>
#include <QtCore/QSignalMapper>
#include <thread>
#include "zemaxqt.h"
#include "basesetting.h"
#pragma execution_character_set("utf-8")

using namespace std;
void zemaxqt::buildReportTab(zemaxqt* zemaxmainwidow) {
	cout << "buildReportTab�̵߳�id: " << this_thread::get_id() << endl;
	string asd = Project1.inputFile;
	//����reportdock���ڲ�����textEditչʾ��ȡ�����в���
	vector<DATA> v = Project1.getLensProperties();
	cout <<"buildReportDock" <<endl;
	//QDockWidget* reportDock = new QDockWidget(tr("Report"), zemaxmainwidow);
	//����������Tab
	QTextEdit* tab_report;
	int count = ui->tabWidget->count();
	tab_report= new QTextEdit(ui->tabWidget);
	ui->tabWidget->addTab(tab_report, tr("Report"));//�ں�����Ӵ�ͼ���ѡ�
	//int cnt = ui->tabWidget->currentIndex();
	//cout << "tabnumber:::" << cnt << endl;
	////��dock�м���txt
	//QTextEdit* textEditReport = new QTextEdit(ui->tabWidget);
	////����textEditReport��С
	//textEditReport->move(10,10);
	//textEditReport->resize(500, 500);

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i].mykey << ":" << v[i].ivalue << "+" << v[i].dvalue << "+" << v[i].svalue << endl;
	}

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].mykey != "NULL") {
			tab_report->append(QString::fromStdString(v[i].mykey) + ":");
		}

		if (v[i].ivalue != 0) {
			tab_report->append(QString::fromStdString(to_string(v[i].ivalue)));
		}

		if (v[i].dvalue != 0) {
			tab_report->append(QString::fromStdString(to_string(v[i].dvalue)));
		}

		if (v[i].svalue != "NULL") {
			tab_report->append(QString::fromStdString(v[i].svalue));
		}
		tab_report->append("\n");
	}
}

void zemaxqt::buildDistoritionTab(zemaxqt* zemaxmainwidow) {
	/*
	* �趨imageheight imagewidth wavelengthNumber wavelength fieldtype Scantype������Ȼ�������������ָ��imageheight��imagewidth����ֵ��
	* ��ǰ��ָ��������Ԥ�����ڶ�Ӧ��label�С�Ҫʵ���ֶ��Ĳ�����������ֵ���OK��������г�����������������ʾ
	* ע���explore��Ŀ�Ľ�����
	*/

	//��ȡ���趨��Ĳ���
	vector<ANYData>  params_setting = Project1.getYourSetting();
	
	//--------------------�����-----------------------------------
	//����buildDistoritionTab
	cout << "buildDistoritionTab" << endl;
	//QDockWidget* DistoritionTab = new QDockWidget(tr("Distorition"), zemaxmainwidow);
	//����������Tab,tabWidget�൱��һ�������������������ؼ�������tab֮�С�
	//tab_DistoritionTab =new QWidget(zemaxmainwidow);

	QWidget* tab_DistoritionTab;
	tab_DistoritionTab = new QWidget(ui->tabWidget);
	ui->tabWidget->addTab(tab_DistoritionTab,tr("Distorition"));

	//1��ImageHeight��
	QLabel* labelImageHeight = new QLabel(tab_DistoritionTab);
	labelImageHeight->setText("ImageHeight:");

	lineEditlabelImageHeight = new QLineEdit(tab_DistoritionTab);
	lineEditlabelImageHeight->setValidator(new QRegularExpressionValidator(QRegularExpression("([0-9]{0,4}[\.][0-9]{1,6})"), lineEditlabelImageHeight)); 

	//2��ImageWidth��
	QLabel* labelImageWidth = new QLabel(tab_DistoritionTab);
	labelImageWidth->setText("ImageWidth:");
	lineEditlabelImageWidth = new QLineEdit(tab_DistoritionTab);
	lineEditlabelImageWidth->setValidator(new QRegularExpressionValidator(QRegularExpression("([0-9]{0,4}[\.][0-9]{1,6})"), lineEditlabelImageWidth)); // ����200���ַ�

	//3��WavelengthNumber��
	QLabel* labelWavelengthNumber = new QLabel(tab_DistoritionTab);
	labelWavelengthNumber->setText("WavelengthNumber:");
	spinBoxWavelengthNumber = new QSpinBox(tab_DistoritionTab);
	//--------------
	spinBoxWavelengthNumber->setValue(Project1.pwav);
	spinBoxWavelengthNumber->setRange(1, Project1.max_wave);

	//4��wavelengthvalue��
	QLabel* labelWaveLength = new QLabel(tab_DistoritionTab);
	labelWaveLength->setText("WaveLength:");
	lineWaveLengthValue = new QLineEdit(tab_DistoritionTab);
	lineWaveLengthValue->setReadOnly(true);
	//---------------
	WavelengthNumber=spinBoxWavelengthNumber->value();
	double WLT1 = Project1.sysWave->GetWavelength(WavelengthNumber)->Wavelength;
	lineWaveLengthValue->setText(QString::fromStdString(to_string(WLT1)));
	//WavelengthNumber��ǰ���ֶ��ı�ʱ����Ҫ����Wavelength��ֵ�ĸı�   https://blog.csdn.net/LebronBear/article/details/114310927
	//connect(spinBoxWavelengthNumber, SIGNAL(valueChanged(int)), zemaxmainwidow, SLOT(WavelengthChangeSlot()));

	//5��FieldType��-������Ҫ������ѡ��
	QLabel* labelFieldType = new QLabel(tab_DistoritionTab);
	labelFieldType->setText("FieldType:");
	ComboBoxFieldType= new QComboBox(tab_DistoritionTab);

	QStringList strListFieldType;
	strListFieldType << "FieldType_Angle" << "FieldType_ObjectHeight" << "FieldType_ParaxialImageHeight" << "FieldType_RealImageHeight" << "FieldType_TheodoliteAngle";
	ComboBoxFieldType->addItems(strListFieldType);
	fieldtypecurrentIndex = int(initialfieldtype);
	ComboBoxFieldType->setCurrentIndex(fieldtypecurrentIndex);
	//���趨Imageheight��С��Χ��Ȼ���趨FieldType��Ĭ�϶���zmx�Դ�������
	fieldY = Project1.TheSystem->SystemData->Fields->GetField(Project1.SystemImageheightMaxIndex)->Y;
	fieldX = Project1.TheSystem->SystemData->Fields->GetField(Project1.SystemImageheightMaxIndex)->X;
	Project1.TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)fieldtypecurrentIndex);
	cout << "YYYYYY:::::" << fieldY << endl;
	lineEditlabelImageHeight->setText(QString::fromStdString(to_string(fieldY)));
	lineEditlabelImageWidth->setText(QString::fromStdString(to_string(fieldX)));
	//connect(ComboBoxFieldType, SIGNAL(currentIndexChanged(int)), zemaxmainwidow, SLOT(ImageHeightWidthChangeSlot()));

	//6��ScanType��-�ṩx,yѡ��
	QLabel* labelScanType = new QLabel(tab_DistoritionTab);
	labelScanType->setText("ScanType:");
	ComboBoxScanType = new QComboBox(tab_DistoritionTab);
	QStringList strListScanType;
	strListScanType << "+y" << "+x" << "-y" << "-x" ;
	ComboBoxScanType->addItems(strListScanType);
	ScanTypecurrentIndex = 0;
	ComboBoxScanType->setCurrentIndex(ScanTypecurrentIndex);
	//connect(ComboBoxScanType, QOverload<int>::of(&QComboBox::currentIndexChanged), ComboBoxScanType, [=]() {
	//	ScanTypecurrentIndex = ComboBoxScanType->currentIndex();
	//	});
	//cout << "ScanTypecurrentIndex::::"<<ScanTypecurrentIndex << endl;

	// 7)��dock�м���txt����չʾdistortion��Ľ��
	textEditResult = new QTextEdit(tab_DistoritionTab);
	textEditResult->setReadOnly(true);

	//DistortionChangeSlot();

	//���һ��button��������κθı���button�ɵ��������������е����ݽ��м��㡣
	QPushButton* DistoritionButton = new QPushButton(tab_DistoritionTab);
	DistoritionButton->setText("Calculate!");

	//connect(DistoritionButton, SIGNAL(clicked(bool)), zemaxmainwidow, SLOT(DistortionChangeSlot()));
	//--------------------���ֲ�-----------------------------------
	// ����ˮƽ�ʹ�ֱҳ�沼�ֹ������-�Ƚ���ҷֿ�����Ϊˮƽ�ģ�Ȼ���ٽ�ˮƽ�Ķ���洢����ֱ�ġ�
	QHBoxLayout* hlayout1 = new QHBoxLayout;
	hlayout1->addWidget(labelImageHeight);
	hlayout1->addWidget(lineEditlabelImageHeight);
	hlayout1->addWidget(labelImageWidth );
	hlayout1->addWidget(lineEditlabelImageWidth);

	QHBoxLayout* hlayout2 = new QHBoxLayout;
	hlayout2->addWidget(labelWavelengthNumber);
	hlayout2->addWidget(spinBoxWavelengthNumber);
	hlayout2->addWidget(labelWaveLength);
	hlayout2->addWidget(lineWaveLengthValue);

	QHBoxLayout* hlayout3 = new QHBoxLayout;
	hlayout3->addWidget(labelFieldType);
	hlayout3->addWidget(ComboBoxFieldType);
	hlayout3->addWidget(labelScanType);
	hlayout3->addWidget(ComboBoxScanType);

	QHBoxLayout* hlayout4 = new QHBoxLayout;
	hlayout4->addWidget(DistoritionButton);

	QHBoxLayout* hlayout5 = new QHBoxLayout;
	hlayout5->addWidget(textEditResult);

	//������ˮƽ���ֵĿؼ���ͳһ���д�ֱ���֡�
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addLayout(hlayout1);
	layout->addLayout(hlayout2);
	layout->addLayout(hlayout3);
	layout->addLayout(hlayout4);
	layout->addLayout(hlayout5);

	tab_DistoritionTab->setLayout(layout);
	QWidget* pWidget = new QWidget(tab_DistoritionTab);  // ����Widget���ֵ��ص㣡����
	pWidget->setLayout(layout);
}

void zemaxqt::buildDistoritionTabConnects(zemaxqt* zemaxmainwidow) {
	connect(spinBoxWavelengthNumber, SIGNAL(valueChanged(int)), zemaxmainwidow, SLOT(WavelengthChangeSlot()));
	connect(ComboBoxFieldType, SIGNAL(currentIndexChanged(int)), zemaxmainwidow, SLOT(ImageHeightWidthChangeSlot()));
	connect(ComboBoxScanType, QOverload<int>::of(&QComboBox::currentIndexChanged), ComboBoxScanType, [=]() {
		ScanTypecurrentIndex = ComboBoxScanType->currentIndex();
		});
	cout << "ScanTypecurrentIndex::::" << ScanTypecurrentIndex << endl;

	connect(DistoritionButton, SIGNAL(clicked(bool)), zemaxmainwidow, SLOT(DistortionChangeSlot()));
}
