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
	cout << "buildReportTab线程的id: " << this_thread::get_id() << endl;
	string asd = Project1.inputFile;
	//构建reportdock，内部设置textEdit展示获取的所有参数
	vector<DATA> v = Project1.getLensProperties();
	cout <<"buildReportDock" <<endl;
	//QDockWidget* reportDock = new QDockWidget(tr("Report"), zemaxmainwidow);
	//构建并接入Tab
	QTextEdit* tab_report;
	int count = ui->tabWidget->count();
	tab_report= new QTextEdit(ui->tabWidget);
	ui->tabWidget->addTab(tab_report, tr("Report"));//在后面添加带图标的选项卡
	//int cnt = ui->tabWidget->currentIndex();
	//cout << "tabnumber:::" << cnt << endl;
	////在dock中加载txt
	//QTextEdit* textEditReport = new QTextEdit(ui->tabWidget);
	////设置textEditReport大小
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
	* 设定imageheight imagewidth wavelengthNumber wavelength fieldtype Scantype条件，然后根据条件生成指定imageheight或imagewidth的数值：
	* 提前将指定的数据预放置在对应的label中。要实现手动的操作，输入数值点击OK则可以运行出结果，或给出错误提示
	* 注意和explore栏目的交互。
	*/

	//获取并设定后的参数
	vector<ANYData>  params_setting = Project1.getYourSetting();
	
	//--------------------界面层-----------------------------------
	//构建buildDistoritionTab
	cout << "buildDistoritionTab" << endl;
	//QDockWidget* DistoritionTab = new QDockWidget(tr("Distorition"), zemaxmainwidow);
	//构建并接入Tab,tabWidget相当于一个容器，将所有其他控件容括在tab之中。
	//tab_DistoritionTab =new QWidget(zemaxmainwidow);

	QWidget* tab_DistoritionTab;
	tab_DistoritionTab = new QWidget(ui->tabWidget);
	ui->tabWidget->addTab(tab_DistoritionTab,tr("Distorition"));

	//1）ImageHeight框
	QLabel* labelImageHeight = new QLabel(tab_DistoritionTab);
	labelImageHeight->setText("ImageHeight:");

	lineEditlabelImageHeight = new QLineEdit(tab_DistoritionTab);
	lineEditlabelImageHeight->setValidator(new QRegularExpressionValidator(QRegularExpression("([0-9]{0,4}[\.][0-9]{1,6})"), lineEditlabelImageHeight)); 

	//2）ImageWidth框
	QLabel* labelImageWidth = new QLabel(tab_DistoritionTab);
	labelImageWidth->setText("ImageWidth:");
	lineEditlabelImageWidth = new QLineEdit(tab_DistoritionTab);
	lineEditlabelImageWidth->setValidator(new QRegularExpressionValidator(QRegularExpression("([0-9]{0,4}[\.][0-9]{1,6})"), lineEditlabelImageWidth)); // 输入200个字符

	//3）WavelengthNumber框
	QLabel* labelWavelengthNumber = new QLabel(tab_DistoritionTab);
	labelWavelengthNumber->setText("WavelengthNumber:");
	spinBoxWavelengthNumber = new QSpinBox(tab_DistoritionTab);
	//--------------
	spinBoxWavelengthNumber->setValue(Project1.pwav);
	spinBoxWavelengthNumber->setRange(1, Project1.max_wave);

	//4）wavelengthvalue框
	QLabel* labelWaveLength = new QLabel(tab_DistoritionTab);
	labelWaveLength->setText("WaveLength:");
	lineWaveLengthValue = new QLineEdit(tab_DistoritionTab);
	lineWaveLengthValue->setReadOnly(true);
	//---------------
	WavelengthNumber=spinBoxWavelengthNumber->value();
	double WLT1 = Project1.sysWave->GetWavelength(WavelengthNumber)->Wavelength;
	lineWaveLengthValue->setText(QString::fromStdString(to_string(WLT1)));
	//WavelengthNumber在前端手动改变时就需要触发Wavelength数值的改变   https://blog.csdn.net/LebronBear/article/details/114310927
	//connect(spinBoxWavelengthNumber, SIGNAL(valueChanged(int)), zemaxmainwidow, SLOT(WavelengthChangeSlot()));

	//5）FieldType框-给出主要的三种选择
	QLabel* labelFieldType = new QLabel(tab_DistoritionTab);
	labelFieldType->setText("FieldType:");
	ComboBoxFieldType= new QComboBox(tab_DistoritionTab);

	QStringList strListFieldType;
	strListFieldType << "FieldType_Angle" << "FieldType_ObjectHeight" << "FieldType_ParaxialImageHeight" << "FieldType_RealImageHeight" << "FieldType_TheodoliteAngle";
	ComboBoxFieldType->addItems(strListFieldType);
	fieldtypecurrentIndex = int(initialfieldtype);
	ComboBoxFieldType->setCurrentIndex(fieldtypecurrentIndex);
	//先设定Imageheight大小范围，然后设定FieldType，默认都是zmx自带的类型
	fieldY = Project1.TheSystem->SystemData->Fields->GetField(Project1.SystemImageheightMaxIndex)->Y;
	fieldX = Project1.TheSystem->SystemData->Fields->GetField(Project1.SystemImageheightMaxIndex)->X;
	Project1.TheSystem->SystemData->Fields->ConvertToFieldType((FieldType)fieldtypecurrentIndex);
	cout << "YYYYYY:::::" << fieldY << endl;
	lineEditlabelImageHeight->setText(QString::fromStdString(to_string(fieldY)));
	lineEditlabelImageWidth->setText(QString::fromStdString(to_string(fieldX)));
	//connect(ComboBoxFieldType, SIGNAL(currentIndexChanged(int)), zemaxmainwidow, SLOT(ImageHeightWidthChangeSlot()));

	//6）ScanType框-提供x,y选项
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

	// 7)在dock中加载txt用于展示distortion后的结果
	textEditResult = new QTextEdit(tab_DistoritionTab);
	textEditResult->setReadOnly(true);

	//DistortionChangeSlot();

	//添加一个button，如果有任何改变则button可点击，点击后按照现有的数据进行计算。
	QPushButton* DistoritionButton = new QPushButton(tab_DistoritionTab);
	DistoritionButton->setText("Calculate!");

	//connect(DistoritionButton, SIGNAL(clicked(bool)), zemaxmainwidow, SLOT(DistortionChangeSlot()));
	//--------------------布局层-----------------------------------
	// 创建水平和垂直页面布局管理对象-先将大家分开保存为水平的，然后再将水平的对象存储到垂直的。
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

	//对上述水平布局的控件再统一进行垂直布局。
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addLayout(hlayout1);
	layout->addLayout(hlayout2);
	layout->addLayout(hlayout3);
	layout->addLayout(hlayout4);
	layout->addLayout(hlayout5);

	tab_DistoritionTab->setLayout(layout);
	QWidget* pWidget = new QWidget(tab_DistoritionTab);  // 这是Widget布局的重点！！！
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
