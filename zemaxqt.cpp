#include "stdafx.h"

#include "zemaxqt.h"
#include <iostream>
#include <QtCore/qstring.h>
#include <QTSql/QSqlQuery>
#include <ActiveQt/activeqtversion.h>
#include <QtWidgets/QFileDialog>
#include <QtCore/QDebug>
#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDockWidget>
#include <thread>
#include <atlstr.h>

#pragma execution_character_set("utf-8")
zemaxqt_subweight subweight;

using namespace std;
vector<string> readfile(string filename);

string PathName;
bool checkDistortionMultiple, checkChiefRayAngleMultiple, checkRelativeIlluminationMultiple,
checkFFTPSFMultiple, checkHuygensPSFMultiple;
int Dis_whichwave, Dis_Fieldtypeindex, Dis_Distortiontype, Dis_Scantype;
int CRA_whichwave, CRA_direction;
int RI_whichwave, RI_direction;
int FFT_whichwave, FFT_Fieldtypeindex, FFT_Scantype, FFT_sampling, FFT_display, FFT_type, FFT_normalize; double FFT_imagedelta;
int Huygens_whichwave, Huygens_Fieldtypeindex, Huygens_Scantype, Huygens_sampling, Huygens_display, Huygens_type, Huygens_normalize; double Huygens_imagedelta;
int rayaming;

int returncode=123456789;
int dwPid = -1;
int waitsubprocessfinish(vector<ANYData> params);
int KillProcess(int pid);
void processfinish(int pid);

//֮�����ں�̨����ʵ����һ����ΪQT�ر��˹��캯�����ε�;��������һ�������һ��ʵ�������µĽ���Ϳ��ԡ�
zemaxqt::zemaxqt(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //��̨����zemax����������г�ʼ��������Ԥ�ȼ���һ��zmx�ļ���
    Project1.createApplication();
    cout << "outputFolderoutputFolder:" << Project1.outputFolder << endl;
    ui->lineEdit_outputpath->setText(QString::fromStdString(Project1.outputFolder));
    cout << "createApplication is complished" << endl;
    PathName = Project1.sampleDir + "/LENS.ZMX";
    Project1.inputFile = PathName.c_str();
    Project1.file_name = "LENS.ZMX";
    int fileexist= Project1.loadmyFile(PathName.c_str());
    if (!fileexist) { ui->textEdit->clear(); ui->textEdit->setText("You need to run THE Example before running this example!"); }
    Project1.basicSetting();
    Project1.propertySetting();
    Project1.getLensProperties();
    MakeYourSetting();
    ////�ź����-��������
    // �����Ĭ�ϵ�����tab
    //ui->tabWidget->clear();
    ui->tabWidget->tabBar()->setTabButton(0, QTabBar::RightSide, NULL);
    ui->tabWidget->removeTab(1);
    // ����menuAnalyse����report�ƶ�����һ��manue
    ui->menuAnalyse->menuAction()->setVisible(false);
    ui->Reports->setVisible(false);
    m_pTimer = new QTimer(this);

    //------------------------------------------------

    ////�ź����-������Ŀ
    connect(ui->actionopen, SIGNAL(triggered()), this, SLOT(openfile_slot()));
    //_bstr_t openpath = "C:\\Users\\admin\\Documents\\Zemax\\Samples\\Sequential\\Objectives\\"+ filename;
    //����.zmx�ļ��Ļ�������
    connect(ui->Reports, SIGNAL(triggered()), this,SLOT(Reports_slot()));
    //����Distortion
    connect(ui->actionDistorition, SIGNAL(triggered()), this, SLOT(Distorition_slot()));
    //tabWidget�ĸ�������-�ܹ��ر�ÿ��tab
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTabSlot(int)));
    //�ر�ui
    connect(ui->actionclose, SIGNAL(triggered()), this, SLOT(close_slot()));
    //field and wavelength max min verification
    connect(ui->pushButton_outputpath, SIGNAL(clicked()), this, SLOT(on_openSrcDirPushButton_clicked()));



    connect(ui->lineEditFieldHTNumber, SIGNAL(textChanged(QString)), this, SLOT(FieldHTNumberverify()));
    connect(ui->lineEditFieldHTMax, SIGNAL(editingFinished()), this, SLOT(FieldHTMaxverify()));
    connect(ui->lineEditFieldHTMin, SIGNAL(editingFinished()), this, SLOT(FieldHTMinverify()));
    connect(ui->comboBoxAllFieldtype, SIGNAL(currentIndexChanged(int)), this, SLOT(AllFieldtypeverifyandFieldHTMaxChange()));
    //���һ��SLOT��ֻҪfieldtype�ı䣬FieldHTMax:Ҳ���Ÿı䡣

    connect(ui->lineEditWavelengthNumber, SIGNAL(textChanged(QString)), this, SLOT(WavelengthNumberverify()));
    connect(ui->lineEditWavelengthMax, SIGNAL(editingFinished()), this, SLOT(WavelengthMaxverify()));
    connect(ui->lineEditWavelengthMin, SIGNAL(editingFinished()), this, SLOT(WavelengthMinverify()));

    connect(ui->comboBoxAllSampling, SIGNAL(currentIndexChanged(int)), this, SLOT(AllSamplingsizeverify()));
    connect(ui->comboBoxAllDisplay, SIGNAL(currentIndexChanged(int)), this, SLOT(AllDisplaysizeverify()));
    connect(ui->lineEditAllImageDelta, SIGNAL(textChanged(QString)), this, SLOT(AllImageDeltaverify()));
    // ����һ��QThread::exec()�����dwPid���м�أ�ֻҪ�ı�ͷ����źš�
    // recordsubweight��
    connect(&subweight, SIGNAL(dwPidchangeSignal(int)), this,SLOT(dwPidchangeSlot(int)) );
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(TasksScheduleSlot()));
}
//�趨·��
void zemaxqt::on_openSrcDirPushButton_clicked()
{
    QString srcDirPath = QFileDialog::getExistingDirectory(
        this, "choose src Directory",
        "/");

    if (srcDirPath.isEmpty())
    {
        return;
    }
    else
    {
        qDebug() << "srcDirPath=" << srcDirPath;
        srcDirPath += "/";
    }
    Project1.outputFolder = srcDirPath.toStdString().c_str();
    ui->lineEdit_outputpath->setText(srcDirPath);

    if (0 != _access(Project1.outputFolder.c_str(), 0))
    {
        // if this folder not exist, create a new one.

        if (Project1.createDirectory(outputFolder))   // return 0, if successfully created
        {
            fprintf(stderr, "error: cannot create folder '%s', ", outputFolder.c_str());
            fprintf(stderr, "in File '%s', line %d. \n", __FILE__, __LINE__);
            exit(1);
        }
    }
    Project1.getLensProperties();
}



//�ź���۲���֪ʶ�Ϳ���ֱ��ʹ���ˡ�
//���ļ���ѡ���ļ���������·������Ϊ�򿪵���Ŀ·����
void zemaxqt::openfile_slot() {
    PathName = inputandverifythefile();
    if (PathName == "NULL") {
        ui->textEdit->clear();
        ui->textEdit->insertPlainText("You need to choose THE Example before running this example!");
    }
    else {
        Project1.inputFile = PathName.c_str();
        int fileexist = Project1.loadmyFile(Project1.inputFile);
        if (!fileexist) { ui->textEdit->clear(); ui->textEdit->setText("You need to run THE Example before running this example!"); }

        //���������һ��exploreSetting,propertySetting,Lensparameter������explore����
        Project1.basicSetting();
        Project1.propertySetting();
        Project1.getLensProperties();
        //�ļ�·��������ߵȲ���Ҫ����Ԥ�����
        Tab0Setting(); WavelengthFieldSetting(); ExploreSetting(); TasksRunningSetting();
        //TasksRelatedSetting����ÿ�θ���file���ø��¡�
        TasksRelatedSetting();


        //2��QTǰ���Ķ�չʾ��ͷ����
        //vector<string> text=readfile(PathName);
        //for(int a=0;a<text.size(); a++)
        //    //���������ı���ע�⣺�˴����������ϳ�һ����.zmx������execl���������ݱ����zemax��̨�л�ȡ��
        //    ui->textEdit->insertPlainText(QString::fromStdString(text[a]));

        ui->textEdit->clear();
        ui->textEdit->insertPlainText("Example Running Successful!");
        if (reporttap_flag) buildReportTab(this);
        if (DistoritionTab_flag)buildDistoritionTab(this);
    }
}

//��ȡ����
void zemaxqt::Reports_slot() {
    tab_report = new QTextEdit(ui->tabWidget);
    //����������Tab
    ui->tabWidget->addTab(tab_report, tr("Report"));//�ں�����Ӵ�ͼ���ѡ�

    buildReportTab(this);
    ui->Reports->setEnabled(false);
    reporttabindex = ui->tabWidget->currentIndex();
    reporttap_flag = true;
}

//����Distorition�������չʾ�ڸ�������
void zemaxqt::Distorition_slot() {
    //--------------------�����-----------------------------------
    //����buildDistoritionTab
    cout << "buildDistoritionTab" << endl;
    //QDockWidget* DistoritionTab = new QDockWidget(tr("Distorition"), zemaxmainwidow);
    //����������Tab,tabWidget�൱��һ�������������������ؼ�������tab֮�С�
    //tab_DistoritionTab =new QWidget(zemaxmainwidow);
    tab_DistoritionTab = new QWidget(ui->tabWidget);
    ui->tabWidget->addTab(tab_DistoritionTab, tr("Distorition"));

    //1��ImageHeight��
    labelImageHeight = new QLabel(tab_DistoritionTab);
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

    //4��wavelengthvalue��
    QLabel* labelWaveLength = new QLabel(tab_DistoritionTab);
    labelWaveLength->setText("WaveLength:");
    lineWaveLengthValue = new QLineEdit(tab_DistoritionTab);
    lineWaveLengthValue->setReadOnly(true);

    //5��FieldType��-������Ҫ������ѡ��
    QLabel* labelFieldType = new QLabel(tab_DistoritionTab);
    labelFieldType->setText("FieldType:");
    ComboBoxFieldType = new QComboBox(tab_DistoritionTab);
    QStringList strListFieldType;
    strListFieldType << "FieldType_Angle" << "FieldType_ObjectHeight" << "FieldType_ParaxialImageHeight" << "FieldType_RealImageHeight" << "FieldType_TheodoliteAngle";
    ComboBoxFieldType->addItems(strListFieldType);

    //6��ScanType��-�ṩx,yѡ��
    QLabel* labelScanType = new QLabel(tab_DistoritionTab);
    labelScanType->setText("ScanType:");
    ComboBoxScanType = new QComboBox(tab_DistoritionTab);
    QStringList strListScanType;
    strListScanType << "+y" << "+x" << "-y" << "-x";
    ComboBoxScanType->addItems(strListScanType);

    //7)���һ��button��������κθı���button�ɵ��������������е����ݽ��м��㡣
    DistoritionButton = new QPushButton(tab_DistoritionTab);
    DistoritionButton->setText("Calculate!");

    // 8)��dock�м���txt����չʾdistortion��Ľ��
    textEditResult = new QTextEdit(tab_DistoritionTab);
    textEditResult->setReadOnly(true);
    // --------------------���ֲ�-----------------------------------
    // ����ˮƽ�ʹ�ֱҳ�沼�ֹ������-�Ƚ���ҷֿ�����Ϊˮƽ�ģ�Ȼ���ٽ�ˮƽ�Ķ���洢����ֱ�ġ�
    QHBoxLayout* hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(labelImageHeight);
    hlayout1->addWidget(lineEditlabelImageHeight);
    hlayout1->addWidget(labelImageWidth);
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

    //----------------��ʼ�����ݼ���������--------------------------
    buildDistoritionTab(this);
    buildDistoritionTabConnects(this);
    ui->actionDistorition->setEnabled(false);
    actionDistoritiontabindex = ui->tabWidget->currentIndex();
    DistoritionTab_flag = true;
}

//������setting��¼����Ȼ�󴫵ݵ���̨��
void zemaxqt::MakeYourSetting() {
    /*�趨	unsigned int WL_NUM = 31;    double WL_MIN = 0.400;    double WL_MAX = 0.700;
    unsigned int IMGHT_NUM = 91; double IMGHT_MIN = 0.0; double IMGHT_MAX = 20.0;
    Ȼ��ָ��task��Ȼ��ȷ��running��
    */
    //�ļ�·��������ߵ�Ԥ��
    WavelengthFieldSetting();
    TasksRunningSetting();
    //Explore������ã�����rayaming��
    ExploreSetting();
    
    //�������ݵĳ�ʼ��
    TasksRelatedSetting();
    //�Ե�һ��tab���̶�����չʾ��ͬʱ��дtextfile_Baseparameters�������
    Tab0Setting();

    /*
    RayAimingMethod
        {
    RayAimingMethod_Off = 0,
    RayAimingMethod_Paraxial = 1,
    RayAimingMethod_Real = 2
    };
    */

    //�Ƚ�button����Ϊenable=false�����ɵ����ֱ�����ݷ����ı�ʱ�ٱ�Ϊ�ɵ�����С�
    ui->pushButtonRunning->setEnabled(true);
    ui->pushButtonCanceling->setEnabled(false);
    connect(ui->checkBoxDistortionMultiple, &QCheckBox::stateChanged, this, [=] {
        checkDistortionMultiple = ui->checkBoxDistortionMultiple->isChecked();
        checkChiefRayAngleMultiple = ui->checkBoxChiefRayAngleMultiple->isChecked();
        checkRelativeIlluminationMultiple = ui->checkBoxRelativeIlluminationMultiple->isChecked();
        //���и���Ϊ��ѡ����radioButton_FFTPSFMultiple��radioButton_HuygensPSFMultiple��Ϊ��ѡһ
        checkFFTPSFMultiple = ui->radioButton_FFTPSFMultiple->isChecked();
        checkHuygensPSFMultiple = ui->radioButton_HuygensPSFMultiple->isChecked();

        //checkFFTPSFMultiple = ui->checkBoxFFTPSFMultiple->isChecked();
        //checkHuygensPSFMultiple = ui->checkBoxHuygensPSFMultiple->isChecked();
        if ((dwPid == -1) && (checkDistortionMultiple || checkChiefRayAngleMultiple || checkRelativeIlluminationMultiple
            || checkFFTPSFMultiple || checkHuygensPSFMultiple)) {
            returncode = 123456789;//��֤����ʹ����Ϻ�running button�ɵ�����ɵ��ǰreturncode���뱻��ʼ��
            ui->pushButtonRunning->setEnabled(true);
        }
        else {
            ui->pushButtonRunning->setEnabled(false);
        }
        });

    connect(ui->checkBoxChiefRayAngleMultiple, &QCheckBox::stateChanged, this, [=] {
        checkDistortionMultiple = ui->checkBoxDistortionMultiple->isChecked();
        checkChiefRayAngleMultiple = ui->checkBoxChiefRayAngleMultiple->isChecked();
        checkRelativeIlluminationMultiple = ui->checkBoxRelativeIlluminationMultiple->isChecked();
        checkFFTPSFMultiple = ui->radioButton_FFTPSFMultiple->isChecked();
        checkHuygensPSFMultiple = ui->radioButton_HuygensPSFMultiple->isChecked();
        
        //checkFFTPSFMultiple = ui->checkBoxFFTPSFMultiple->isChecked();
        //checkHuygensPSFMultiple = ui->checkBoxHuygensPSFMultiple->isChecked();
        if ((dwPid == -1) && (checkDistortionMultiple || checkChiefRayAngleMultiple || checkRelativeIlluminationMultiple
            || checkFFTPSFMultiple || checkHuygensPSFMultiple)) {
            returncode = 123456789;
            ui->pushButtonRunning->setEnabled(true);
        }
        else {
            ui->pushButtonRunning->setEnabled(false);
        }
        });
    connect(ui->checkBoxRelativeIlluminationMultiple, &QCheckBox::stateChanged, this, [=] {
        checkDistortionMultiple = ui->checkBoxDistortionMultiple->isChecked();
        checkChiefRayAngleMultiple = ui->checkBoxChiefRayAngleMultiple->isChecked();
        checkRelativeIlluminationMultiple = ui->checkBoxRelativeIlluminationMultiple->isChecked();
        checkFFTPSFMultiple = ui->radioButton_FFTPSFMultiple->isChecked();
        checkHuygensPSFMultiple = ui->radioButton_HuygensPSFMultiple->isChecked();

        //checkFFTPSFMultiple = ui->checkBoxFFTPSFMultiple->isChecked();
        //checkHuygensPSFMultiple = ui->checkBoxHuygensPSFMultiple->isChecked();
        if ((dwPid == -1) && (checkDistortionMultiple || checkChiefRayAngleMultiple || checkRelativeIlluminationMultiple
            || checkFFTPSFMultiple || checkHuygensPSFMultiple)) {
            returncode = 123456789;
            ui->pushButtonRunning->setEnabled(true);
        }
        else {
            ui->pushButtonRunning->setEnabled(false);
        }
        });
    connect(ui->radioButton_FFTPSFMultiple, &QRadioButton::clicked, this, [=] {
        checkDistortionMultiple = ui->checkBoxDistortionMultiple->isChecked();
        checkChiefRayAngleMultiple = ui->checkBoxChiefRayAngleMultiple->isChecked();
        checkRelativeIlluminationMultiple = ui->checkBoxRelativeIlluminationMultiple->isChecked();
        checkFFTPSFMultiple = ui->radioButton_FFTPSFMultiple->isChecked();
        checkHuygensPSFMultiple = ui->radioButton_HuygensPSFMultiple->isChecked();

        //checkFFTPSFMultiple = ui->checkBoxFFTPSFMultiple->isChecked();
        //checkHuygensPSFMultiple = ui->checkBoxHuygensPSFMultiple->isChecked();
        if ((dwPid == -1) && (checkDistortionMultiple || checkChiefRayAngleMultiple || checkRelativeIlluminationMultiple
            || checkFFTPSFMultiple || checkHuygensPSFMultiple)) {
            returncode = 123456789;
            ui->pushButtonRunning->setEnabled(true);
        }
        else {
            ui->pushButtonRunning->setEnabled(false);
        }
        });
    connect(ui->radioButton_HuygensPSFMultiple, &QRadioButton::clicked, this, [=] {
        checkDistortionMultiple = ui->checkBoxDistortionMultiple->isChecked();
        checkChiefRayAngleMultiple = ui->checkBoxChiefRayAngleMultiple->isChecked();
        checkRelativeIlluminationMultiple = ui->checkBoxRelativeIlluminationMultiple->isChecked();
        checkFFTPSFMultiple = ui->radioButton_FFTPSFMultiple->isChecked();
        checkHuygensPSFMultiple = ui->radioButton_HuygensPSFMultiple->isChecked();

        //checkFFTPSFMultiple = ui->checkBoxFFTPSFMultiple->isChecked();
        //checkHuygensPSFMultiple = ui->checkBoxHuygensPSFMultiple->isChecked();
        if ((dwPid==-1) && (checkDistortionMultiple || checkChiefRayAngleMultiple || checkRelativeIlluminationMultiple
            || checkFFTPSFMultiple || checkHuygensPSFMultiple)) {
            returncode = 123456789;
            ui->pushButtonRunning->setEnabled(true);
        }
        else {
            ui->pushButtonRunning->setEnabled(false);
        }
        });


    //������forѭ����tasks���õ�QApplication::processEvents()�����С�
    auto tasksWhile = [=]()
    {
        //Tab0Setting�����ݺ�getLensProperties��Ҫ����ui�޸ĺ�����ݡ�
        Tab0Setting();
        //breakflage���ڿ���forѭ���Ƿ�������
        Project1.breakflage = 0;
        ui->pushButtonRunning->setEnabled(false);
        m_pTimer->start(1000);
        //�����߳�

        //-----------------------1���ļ�·��������ߣ�-------------------------------------
     //�������ʱ�����е����ݸ���һ�Σ����Զ�private���ݽ��и��¡�
        QString wlnum = ui->lineEditWavelengthNumber->text();
        Project1.set_WL_NUM(wlnum.toDouble());
        double wlmin = ((ui->lineEditWavelengthMin->text()).toDouble()) / 1000;//nm-um
        Project1.set_WL_MIN(wlmin);
        double wlmax = ((ui->lineEditWavelengthMax->text()).toDouble()) / 1000;//nm-um
        Project1.set_WL_MAX(wlmax);

        QString imghtnum = ui->lineEditFieldHTNumber->text();
        Project1.set_IMGHT_NUM(imghtnum.toUInt());
        QString imghtmin = ui->lineEditFieldHTMin->text();
        Project1.set_IMGHT_MIN(imghtmin.toDouble());
        QString imghtmax = ui->lineEditFieldHTMax->text();
        Project1.set_IMGHT_MAX(imghtmax.toDouble());

        QString imgwtnum = ui->lineEditFieldHTNumber->text();
        Project1.set_IMGWT_NUM(imgwtnum.toUInt());
        QString imgwtmin = ui->lineEditFieldHTMin->text();
        Project1.set_IMGWT_MIN(imgwtmin.toDouble());
        QString imgwtmax = ui->lineEditFieldHTMax->text();
        Project1.set_IMGWT_MAX(imgwtmax.toDouble());
        //---------------------2)MultipleTask����ѡ�����趨----------------------------------
        checkDistortionMultiple = ui->checkBoxDistortionMultiple->isChecked();
        checkChiefRayAngleMultiple = ui->checkBoxChiefRayAngleMultiple->isChecked();
        checkRelativeIlluminationMultiple = ui->checkBoxRelativeIlluminationMultiple->isChecked();
        checkFFTPSFMultiple = ui->radioButton_FFTPSFMultiple->isChecked();
        checkHuygensPSFMultiple = ui->radioButton_HuygensPSFMultiple->isChecked();

        //checkFFTPSFMultiple = ui->checkBoxFFTPSFMultiple->isChecked();
        //checkHuygensPSFMultiple = ui->checkBoxHuygensPSFMultiple->isChecked();

        //DistortionMultiple Related Setting
        QString lEwt = ui->lineEditWhichwave->text();
        Dis_whichwave = lEwt.toInt();
        Dis_Fieldtypeindex = ui->comboBoxFieldtype->currentIndex();//0 Angle,1 RealImageHeight,2 ParaxialImageHeight,3 RealImageHeight,4 TheodoliteAngle
        Dis_Distortiontype = ui->comboBoxDistortiontype->currentIndex();
        Dis_Scantype = ui->comboBoxScantype->currentIndex();

        //CRAMultiple Related Setting
        QString lEwt2 = ui->lineEditWhichwave_2->text();
        CRA_whichwave = lEwt2.toInt();
        CRA_direction = ui->comboDirection_2->currentIndex();

        //RIMultiple Related Setting
        QString lEwt3 = ui->lineEditWhichwave_3->text();
        RI_whichwave = lEwt3.toInt();
        RI_direction = ui->comboDirection_3->currentIndex();

        //FFTPSFMultiple Related Setting
        FFT_whichwave = (ui->lineEditWhichwave_4->text()).toInt();
        FFT_Fieldtypeindex = ui->comboBoxFieldtype_4->currentIndex();//0 Angle,1 RealImageHeight,2 ParaxialImageHeight,3 RealImageHeight,4 TheodoliteAngle
        FFT_Scantype = ui->comboBoxScantype_4->currentIndex();
        FFT_sampling = ui->comboBoxSampling_4->currentIndex();
        FFT_display = ui->comboBoxDisplay_4->currentIndex();
        FFT_type = ui->comboBoxType_4->currentIndex();
        FFT_imagedelta = (ui->lineEditImageDelta_4->text()).toDouble();
        FFT_normalize = ui->checkBoxNormalize_4->isChecked();

        //HuygensPSFMultiple Related Setting
        Huygens_whichwave = (ui->lineEditWhichwave_5->text()).toInt();
        Huygens_Fieldtypeindex = ui->comboBoxFieldtype_5->currentIndex();//0 Angle,1 RealImageHeight,2 ParaxialImageHeight,3 RealImageHeight,4 TheodoliteAngle
        Huygens_Scantype = ui->comboBoxScantype_5->currentIndex();
        Huygens_sampling = ui->comboBoxSampling_5->currentIndex();
        Huygens_display = ui->comboBoxDisplay_5->currentIndex();
        Huygens_type = ui->comboBoxType_5->currentIndex();
        Huygens_imagedelta = (ui->lineEditImageDelta_5->text()).toDouble();
        Huygens_normalize = ui->checkBoxNormalize_5->isChecked();

        //-----------------------3��������Ҫ���ã���rayaming------------------------------------
        rayaming = ui->comboBoxRayAiming->currentIndex();

        //if (checkDistortionMultiple || checkChiefRayAngleMultiple || checkRelativeIlluminationMultiple
        //    || checkFFTPSFMultiple || checkHuygensPSFMultiple) {
        //    //��һ�����̣�������background�����������������ȡ��������pid
        //    //����Ҫ�غ��߳���ɲ������ɺ�ķ���ֵ���ܽ�buttonתΪ�ɵ����Ȼ��
        //    ui->pushButtonRunning->setEnabled(false);
        //    ui->pushButtonCanceling->setEnabled(true);
        //    vector<ANYData> params = Project1.getYourSetting();
        //    //����ChiefRayAngleMultiple�������չʾ��textEdit
        //    std::thread t1(waitsubprocessfinish, params);
        //    t1.detach();
        //    Sleep(3000);//�����ܱ�֤�����Ѿ����������
        //    if (dwPid != -1)                 //˵�������Ѿ�������δ������=-1˵��û��ʼ���Ѿ�����
        //    {
        //        ui->textEdit->clear();
        //        ui->textEdit->setText("Create Process Succeed!");
        //    }
        //    else if(returncode == 0) {       //˵������û�п������ó�����
        //        ui->textEdit->clear();
        //        ui->textEdit->setText("Create Process Error!Or Self-killed In 3 Seconds");
        //        returncode == 123456789;
        //        ui->pushButtonRunning->setEnabled(true);
        //        ui->pushButtonCanceling->setEnabled(false);
        //    } 
        //    //����Ҳ��Ϊreturncode��ͬ�������������Ƶ���أ���ͬ��code��ζ�Ų�ͬ�����״����
        //    else{//˵������û��ʼ�������Ѿ�������˵��������3�������г���������
        //        ui->textEdit->clear();
        //        ui->textEdit->setText("Program Running Error!");
        //        returncode == 123456789;
        //        ui->pushButtonRunning->setEnabled(true);
        //        ui->pushButtonCanceling->setEnabled(false);
        //    }
        //    }

        time_t startdis, enddis, startcra, endcra, startri, endri, startfft, endfft, starthuygens, endhuygens;       // ��ʱ
        double costdis = 0, costcra = 0, costri = 0, costfft = 0, costhuygens = 0;

        ui->pushButtonCanceling->setEnabled(true);

        //�˴������Ѿ������¹���private������
        Project1.outFileName = "optics";
        vector<ANYData> params_setting = Project1.getYourSetting();
        Project1.saveOIToMatFile(params_setting);

        // ���realWorkingFNumber�ֶ�ֵ��ΪeffectiveFNumber
        double rWorkingFNumber = Project1.realWorkingFNumber;
        mxArray* rfNumber = mxCreateDoubleScalar(rWorkingFNumber);
        mxSetField(Project1.oiStruct, 0, "fNumber", rfNumber);

        // ���focalLength�ֶ�ֵ
        double focallength = Project1.EFL;
        mxArray* focalLength = mxCreateDoubleScalar(focallength);
        mxSetField(Project1.oiStruct, 0, "focalLength", focalLength);

        //��rayTrace�ֶ�����Ҫ��5��������Ϊֵ
        // add field 'rayTrace'
        //m_rayTrace = mxCreateStructMatrix(1, 1, 0, nullptr);
        mxAddField(Project1.oiStruct, "rayTrace");
        mxSetField(Project1.oiStruct, 0, "rayTrace", Project1.m_rayTrace);

        //rayTrace�� add field 'program'
        mxAddField(Project1.m_rayTrace, "program");
        mxArray* zemax = mxCreateString("zemax");
        mxSetField(Project1.m_rayTrace, 0, "program", zemax);
        //rayTrace�� add field 'lensFile'
        string file_name = (char*)Project1.file_name;
        string m_lensFile = file_name + ".zmx";
        mxAddField(Project1.m_rayTrace, "lensFile");
        mxArray* lensFile = mxCreateString(m_lensFile.c_str());
        mxSetField(Project1.m_rayTrace, 0, "lensFile", lensFile);
        //rayTrace�� add field 'primarywavelength'
        double m_primarywavelength = Project1.sysWave->GetWavelength(Project1.initpwav)->Wavelength;
        mxAddField(Project1.m_rayTrace, "referenceWavelength");
        mxArray* primarywavelength = mxCreateDoubleScalar(m_primarywavelength * 1000);
        mxSetField(Project1.m_rayTrace, 0, "referenceWavelength", primarywavelength);
        //rayTrace�� add field 'objectDistance'
        double m_objectDistance = Project1.Object_distance;
        mxAddField(Project1.m_rayTrace, "objectDistance");
        mxArray* objectDistance = mxCreateDoubleScalar(m_objectDistance);
        mxSetField(Project1.m_rayTrace, 0, "objectDistance", objectDistance);
        // rayTrace�� add field 'mag'-'paraxialMagnification'
        double m_paraxialMagnification = Project1.paraxialMagnification;
        mxAddField(Project1.m_rayTrace, "mag");
        mxArray* paraxialMagnification = mxCreateDoubleScalar(m_paraxialMagnification);
        mxSetField(Project1.m_rayTrace, 0, "mag", paraxialMagnification);

        ////rayTrace�� add field 'paraxialWorkingFNumber'
        double m_paraxworkingfNumber = Project1.paraxialWorkingFNumber;
        mxAddField(Project1.m_rayTrace, "fFNumber");
        mxArray* pFNumber = mxCreateDoubleScalar(m_paraxworkingfNumber);
        mxSetField(Project1.m_rayTrace, 0, "fFNumber", pFNumber);

        // rayTrace�� add field 'effectiveFocalLength'
        double m_effectivefocalLength = Project1.EFL;
        mxAddField(Project1.m_rayTrace, "effectiveFocalLength");
        mxArray* effFocalLength = mxCreateDoubleScalar(m_effectivefocalLength);
        mxSetField(Project1.m_rayTrace, 0, "effectiveFocalLength", effFocalLength);

        // rayTrace�� add field 'realWorkingfnumber'
        mxAddField(Project1.m_rayTrace, "effectiveFNumber");
        mxArray* rFNumber = mxCreateDoubleScalar(rWorkingFNumber);
        mxSetField(Project1.m_rayTrace, 0, "effectiveFNumber", rFNumber);

        //rayTrace�� add field 'fov'
        long MaxIndex = Project1.SystemImageheightMaxIndex;
        double m_halffov = Project1.TheSystem->SystemData->Fields->GetField(MaxIndex)->Y;
        mxAddField(Project1.m_rayTrace, "fov");
        mxArray* fov = mxCreateDoubleScalar(m_halffov * 2);
        mxSetField(Project1.m_rayTrace, 0, "fov", fov);

        checkDistortionMultipleflag = 0; checkChiefRayAngleMultipleflag = 0; checkRelativeIlluminationMultipleflag = 0;
        checkFFTPSFMultipleflag = 0; checkHuygensPSFMultipleflag=0;
        if (checkDistortionMultiple) {
            checkDistortionMultipleflag = 1;
            startdis = clock();

            //�û����趨�Ĳ�����int whichwave = 1, int Fieldtype = 2, int Distortiontype = 0, int Scantype = 0
            mxArray* mydistortion = Project1.DistortionMultiple(Dis_whichwave, Dis_Fieldtypeindex, Dis_Distortiontype, Dis_Scantype);
            // add field 'Distorition'
            mxAddField(Project1.m_rayTrace, "geometry");
            mxSetField(Project1.m_rayTrace, 0, "geometry", mydistortion);
            enddis = clock();
            costdis = (double)(enddis - startdis) / CLOCKS_PER_SEC;
        }
        if (checkChiefRayAngleMultiple) {
            checkChiefRayAngleMultipleflag = 1;
            startcra = clock();
            //�û����趨�Ĳ�����int whichwave = 1, int Fieldtype = 2, int Distortiontype = 0, int Scantype = 0
            mxArray* mycra = Project1.ChiefRayAngleMultiple(Project1.pwav, Dis_Fieldtypeindex);
            // add field 'CRA'
            mxAddField(Project1.m_rayTrace, "CRA");
            mxSetField(Project1.m_rayTrace, 0, "CRA", mycra);
            endcra = clock();
            costcra = (double)(endcra - startcra) / CLOCKS_PER_SEC;
        }
        if (checkRelativeIlluminationMultiple) {
            checkRelativeIlluminationMultipleflag = 1;
            startri = clock();
            //�û����趨�Ĳ�����int whichwave = 1, int Fieldtype = 2, int Distortiontype = 0, int Scantype = 0
            mxArray* ri = Project1.RIMultiple(Project1.pwav, Dis_Fieldtypeindex);
            // add field 'RI'
            mxAddField(Project1.m_rayTrace, "relIllum");
            mxSetField(Project1.m_rayTrace, 0, "relIllum", ri);
            endri = clock();
            costri = (double)(endri - startri) / CLOCKS_PER_SEC;
        }
        if (checkFFTPSFMultiple) {
            checkFFTPSFMultipleflag = 1;
            startfft = clock();
            //�û����趨�Ĳ�����int whichwave, int Fieldtype, int Samplingsizetype,int Displaysizetype, int fftpsftype, double ImageDelta, bool isNormalize
            mxArray* fftpsf = Project1.FFTPSFMultiple(FFT_whichwave, FFT_Fieldtypeindex, FFT_sampling, FFT_display, FFT_type, FFT_imagedelta, FFT_normalize);
            // add field 'fftpsf'
            mxAddField(Project1.m_rayTrace, "psf");
            mxSetField(Project1.m_rayTrace, 0, "psf", fftpsf);
            endfft = clock();
            costfft = (double)(endfft - startfft) / CLOCKS_PER_SEC;
        }
        if (checkHuygensPSFMultiple) {
            checkHuygensPSFMultipleflag = 1;
            starthuygens = clock();
            //�û����趨�Ĳ�����int whichwave, int Fieldtype, int Samplingsizetype,int displaysizetype, double ImageDelta, int HuygensPSFtype, bool isNormalize
            mxArray* huygenspsf = Project1.HuygensPSFMultiple(Huygens_whichwave, Huygens_Fieldtypeindex, Huygens_sampling, Huygens_display, Huygens_type, Huygens_imagedelta, Huygens_normalize);
            // add field 'fftpsf'
            mxAddField(Project1.m_rayTrace, "Huygenspsf");
            mxSetField(Project1.m_rayTrace, 0, "Huygenspsf", huygenspsf);
            endhuygens = clock();
            costhuygens = (double)(endhuygens - starthuygens) / CLOCKS_PER_SEC;
        }
        //�ڴ˴��رռ�ʱ��
        m_pTimer->stop();

        double totalcost;
        totalcost = costdis + costcra + costri + costfft + costhuygens;
        // write to file
        time_t writestart, writeend; double write;
        writestart = clock();
        matPutVariable(Project1.out_File, Project1.outFileName.c_str(), Project1.oiStruct);
        writeend = clock();
        write = (double)(writeend - writestart) / CLOCKS_PER_SEC;
        cout << "write:::::" << write << endl;
        fstream textfile_Baseparameters;
        textfile_Baseparameters.open(filepath_Baseparameters, fstream::trunc | ios::app);
        textfile_Baseparameters << "writetime= " << write << endl;
        textfile_Baseparameters.close();

        Project1.closemat();
        //�ظ���ť��
        ui->pushButtonCanceling->setEnabled(false);
        ui->pushButtonRunning->setEnabled(true);


        ui->textEdit->setText("Time cost:");
        ui->textEdit->append("Distortion cost:" + QString::fromStdString(to_string(costdis)) + " (s); ");
        ui->textEdit->append("ChiefRayAngle cost:" + QString::fromStdString(to_string(costcra)) + " (s); ");
        ui->textEdit->append("RelativeIllumination cost:" + QString::fromStdString(to_string(costri)) + " (s); ");
        ui->textEdit->append("FFTPSF cost:" + QString::fromStdString(to_string(costfft)) + " (s); ");
        ui->textEdit->append("HuygensPSF cost:" + QString::fromStdString(to_string(costhuygens)) + " (s); ");
        ui->textEdit->append("Total cost:" + QString::fromStdString(to_string(totalcost)) + " (s); ");
        ui->textEdit->append("writetime= " + QString::fromStdString(to_string(write)) + " (s); ");

        //�������Ͻ���������������������Ҫ����һ�±��μ��ص��ļ���
        //emit subweight.dwPidchangeSignal(dwPid);
        int fileexist = Project1.loadmyFile(Project1.inputFile);
        //if (!fileexist) { ui->textEdit->clear(); ui->textEdit->setText(QString::fromStdString(to_string(pwav))); }
        CString msg;
        msg.Format(_T("�ܺ�ʱ:%lf\n"), totalcost);
        MessageBox(0, msg, _T("״̬"), MB_OK | MB_ICONWARNING);
    };

    connect(ui->pushButtonRunning, &QPushButton::clicked, tasksWhile);

    connect(ui->pushButtonCanceling, &QPushButton::clicked, this, [=]() {
        //KillProcess();
        Project1.breakflage=1;

        //mxDestroyArray(oiStruct);
        //matClose(out_File);
        ////dwPid�Ѿ��������ӽ��̵�ֵ����������֮ǰ��Ҫ�ܽ��ý���kill����
        //if (dwPid != -1) {                           //˵�������Ѿ�������δ����
        //    int killstatue = KillProcess(dwPid);
        //    if (killstatue == 1) {
        //        ui->pushButtonCanceling->setEnabled(false);
        //        ui->pushButtonRunning->setEnabled(true);
        //        ui->textEdit->setText("Kill Process Over!");
        //        dwPid = -1; returncode = 123456789;
        //    }
        //    else {
        //        ui->textEdit->clear();
        //        ui->textEdit->setText("Kill Process Error!Please try again.");
        //    }
        //}
        //else {
        //    ui->pushButtonRunning->setEnabled(true);
        //    ui->pushButtonCanceling->setEnabled(false);
        //}
        });
}
void zemaxqt::Tab0Setting() {
    //չʾ�������ݣ�·�������ƣ��������б�Ҫ����
    //����reportdock���ڲ�����textEditչʾ��ȡ�����в���
    vector<DATA> v = Project1.getLensProperties();
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].mykey << ":" << v[i].ivalue << "+" << v[i].dvalue << "+" << v[i].svalue << endl;
    }
    ui->textEdit_tab0->clear();
    if (v.size()!=0) {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].mykey != "NULL") {
                ui->textEdit_tab0->append(QString::fromStdString(v[i].mykey) + ":");
            }

            if (v[i].ivalue != 0) {
                ui->textEdit_tab0->append(QString::fromStdString(to_string(v[i].ivalue)));
            }

            if (v[i].dvalue != 0) {
                ui->textEdit_tab0->append(QString::fromStdString(to_string(v[i].dvalue)));
            }

            if (v[i].svalue != "NULL") {
                ui->textEdit_tab0->append(QString::fromStdString(v[i].svalue));
            }
        }
    }

}
void zemaxqt::WavelengthFieldSetting() {
    ui->comboBoxAllFieldtype->setCurrentIndex(int(Project1.initialfieldtype)); //�趨Fieldtype��ʼ����Ϊϵͳ�Դ���
    
    unsigned int wl_num = Project1.set_WL_NUM(31);
    double wl_min = Project1.set_WL_MIN(0.400);
    double wl_max = Project1.set_WL_MAX(0.700);
    unsigned int imght_num = Project1.set_IMGHT_NUM(90);
    double imght_min = Project1.set_IMGHT_MIN(0.0);
    double imght_max = Project1.set_IMGHT_MAX(Project1.initialfieldYmaxvalue); //�趨imageheightY��ʼֵΪϵͳ�Դ���
    unsigned int imgwt_num = Project1.set_IMGWT_NUM(0);
    double imgwt_min = Project1.set_IMGWT_MIN(0.0);
    double imgwt_max = Project1.set_IMGWT_MAX(0.0);

    ui->lineEditWavelengthNumber->setText(QString::fromStdString(to_string(wl_num)));
    ui->lineEditWavelengthNumber->setValidator(new QRegularExpressionValidator(QRegularExpression("([0-9]{0,4})"), ui->lineEditWavelengthNumber)); // ����200���ַ�
    ui->lineEditWavelengthMin->setText(QString::fromStdString(to_string(wl_min*1000)));//nm
    ui->lineEditWavelengthMin->installEventFilter(this);
    ui->lineEditWavelengthMax->setText(QString::fromStdString(to_string(wl_max * 1000)));//nm
    ui->lineEditWavelengthMax->installEventFilter(this);

    ui->lineEditFieldHTNumber->setText(QString::fromStdString(to_string(imght_num)));
    ui->lineEditFieldHTNumber->setValidator(new QRegularExpressionValidator(QRegularExpression("([0-9]{0,4})"), ui->lineEditFieldHTNumber)); // ����200���ַ�
    ui->lineEditFieldHTMin->setText(QString::fromStdString(to_string(imght_min)));
    ui->lineEditFieldHTMin->installEventFilter(this);
    ui->lineEditFieldHTMax->setText(QString::fromStdString(to_string(imght_max)));
    ui->lineEditFieldHTMax->installEventFilter(this);

                                                                                                                                                     //ui->lineEditFieldWTNumber->setText(QString::fromStdString(to_string(imgwt_num)));
    //ui->lineEditFieldWTNumber->setValidator(new QRegularExpressionValidator(QRegularExpression("([0-9]{0,4})"), ui->lineEditFieldWTNumber)); // ����200���ַ�
    //ui->lineEditFieldWTMin->setText(QString::fromStdString(to_string(imgwt_min)));
    //ui->lineEditFieldWTMin->setValidator(new QRegularExpressionValidator(QRegularExpression("([0-9]{0,4}[\.][0-9]{1,6})"), ui->lineEditFieldWTMin)); // ����200���ַ�
    //ui->lineEditFieldWTMax->setText(QString::fromStdString(to_string(imgwt_max)));
    //ui->lineEditFieldWTMax->setValidator(new QRegularExpressionValidator(QRegularExpression("([0-9]{0,4}[\.][0-9]{1,6})"), ui->lineEditFieldWTMax)); // ����200���ַ�
}
bool zemaxqt::eventFilter(QObject* target, QEvent* event)
{
    if (target == ui->lineEditWavelengthMin && event->type() == QEvent::FocusIn)
    {
        //����ֻ����������
        QRegExpValidator* pRevalidotor = new QRegExpValidator(QRegExp("[0-9]{20}"), this);
        ui->lineEditWavelengthMin->setValidator(pRevalidotor);
        ui->lineEditWavelengthMin->setAttribute(Qt::WA_InputMethodEnabled, false);
    }
    if (target == ui->lineEditWavelengthMin  && event->type() == QEvent::FocusOut)
    {
        if (ui->lineEditWavelengthMin->validator() != nullptr)
        {
            delete ui->lineEditWavelengthMin->validator();
            ui->lineEditWavelengthMin->setValidator(nullptr);
        }
    }

    if (target == ui->lineEditWavelengthMax && event->type() == QEvent::FocusIn)
    {
        //����ֻ����������
        QRegExpValidator* pRevalidotor = new QRegExpValidator(QRegExp("[0-9]{20}"), this);
        ui->lineEditWavelengthMax->setValidator(pRevalidotor);
        ui->lineEditWavelengthMax->setAttribute(Qt::WA_InputMethodEnabled, false);
    }
    if (target == ui->lineEditWavelengthMax && event->type() == QEvent::FocusOut)
    {
        if (ui->lineEditWavelengthMax->validator() != nullptr)
        {
            delete ui->lineEditWavelengthMax->validator();
            ui->lineEditWavelengthMax->setValidator(nullptr);
        }
    }

    if (target == ui->lineEditFieldHTMin && event->type() == QEvent::FocusIn)
    {
        //����ֻ����������
        QRegExpValidator* pRevalidotor = new QRegExpValidator(QRegExp("[0-9]{20}"), this);
        ui->lineEditFieldHTMin->setValidator(pRevalidotor);
        ui->lineEditFieldHTMin->setAttribute(Qt::WA_InputMethodEnabled, false);
    }
    if (target == ui->lineEditFieldHTMin && event->type() == QEvent::FocusOut)
    {
        if (ui->lineEditFieldHTMin->validator() != nullptr)
        {
            delete ui->lineEditFieldHTMin->validator();
            ui->lineEditFieldHTMin->setValidator(nullptr);
        }
    }

    if (target == ui->lineEditFieldHTMax && event->type() == QEvent::FocusIn)
    {
        //����ֻ����������
        QRegExpValidator* pRevalidotor = new QRegExpValidator(QRegExp("[0-9]{20}"), this);
        ui->lineEditFieldHTMax->setValidator(pRevalidotor);
        ui->lineEditFieldHTMax->setAttribute(Qt::WA_InputMethodEnabled, false);
    }
    if (target == ui->lineEditFieldHTMax && event->type() == QEvent::FocusOut)
    {
        if (ui->lineEditFieldHTMax->validator() != nullptr)
        {
            delete ui->lineEditFieldHTMax->validator();
            ui->lineEditFieldHTMax->setValidator(nullptr);
        }
    }
    return QWidget::eventFilter(target, event);
}
void zemaxqt::TasksRunningSetting() {
    //���������
    ui->comboBoxAllSampling->setCurrentIndex(3);
    ui->comboBoxAllDisplay->setCurrentIndex(4);
    ui->lineEditAllImageDelta->setText(QString::fromStdString(to_string(0.25)));//um
    ui->lineEditAllImageDelta->setEnabled(true);
    //ȫ������Ϊ���ɼ�����Ĭ��ȫѡ��
    ui->checkBoxDistortionMultiple->setVisible(false);
    ui->checkBoxChiefRayAngleMultiple->setVisible(false);
    ui->checkBoxRelativeIlluminationMultiple->setVisible(false);
    ui->checkBoxFFTPSFMultiple->setVisible(false);
    ui->checkBoxHuygensPSFMultiple->setVisible(false);
}

void zemaxqt::TasksRelatedSetting() {

    //�ֿ�������
    //DistortionMultiple Related Setting

    ui->lineEditWhichwave->setText(QString::fromStdString(to_string(Project1.pwav)));
    ui->comboBoxFieldtype->setCurrentIndex(ui->comboBoxAllFieldtype->currentIndex()); //0 Angle,1 RealImageHeight,2 ParaxialImageHeight,3 RealImageHeight,4 TheodoliteAngle
    ui->comboBoxDistortiontype->setCurrentIndex(0);
    ui->comboBoxScantype->setCurrentIndex(0);

    //CRAMultiple Related Setting
    ui->lineEditWhichwave_2->setText(QString::fromStdString(to_string(Project1.pwav)));
    ui->comboDirection_2->setCurrentIndex(0);

    //RIMultiple Related Setting
    ui->lineEditWhichwave_3->setText(QString::fromStdString(to_string(Project1.pwav)));
    ui->comboDirection_3->setCurrentIndex(0);

    //FFTPSFMultiple Related Setting
    ui->lineEditWhichwave_4->setText(QString::fromStdString(to_string(Project1.pwav)));
    ui->comboBoxFieldtype_4->setCurrentIndex(ui->comboBoxAllFieldtype->currentIndex());
    ui->comboBoxSampling_4->setCurrentIndex(ui->comboBoxAllSampling->currentIndex());
    ui->comboBoxDisplay_4->setCurrentIndex(ui->comboBoxAllDisplay->currentIndex());
    ui->comboBoxScantype_4->setCurrentIndex(0);
    ui->comboBoxType_4->setCurrentIndex(0);
    double AllImageDelta = (ui->lineEditAllImageDelta->text()).toDouble();
    ui->lineEditImageDelta_4->setText(QString::fromStdString(to_string(AllImageDelta)));  //um
    ui->checkBoxNormalize_4->setChecked(false);

    //HuygensPSFMultiple Related Setting
    ui->lineEditWhichwave_5->setText(QString::fromStdString(to_string(Project1.pwav)));
    ui->comboBoxFieldtype_5->setCurrentIndex(ui->comboBoxAllFieldtype->currentIndex());
    ui->comboBoxSampling_5->setCurrentIndex(ui->comboBoxAllSampling->currentIndex());
    ui->comboBoxDisplay_5->setCurrentIndex(ui->comboBoxAllDisplay->currentIndex());
    ui->comboBoxScantype_5->setCurrentIndex(0);
    ui->comboBoxType_5->setCurrentIndex(0);
    ui->lineEditImageDelta_5->setText(QString::fromStdString(to_string(AllImageDelta))); //um
    ui->checkBoxNormalize_5->setChecked(false);
}

void zemaxqt::ExploreSetting() {
    QStringList strListRayAming;
    RayAimingIndex = Project1.TheSystem->SystemData->RayAiming->GetRayAiming();
    cout << "RayAimingIndex::" << RayAimingIndex << endl;
    //int RayAimingIndex = 2;
    ui->comboBoxRayAiming->setCurrentIndex(RayAimingIndex);
}

string zemaxqt::inputandverifythefile() {
    QString filePathName = QFileDialog::getOpenFileName(this, "open", "../", "souce(*.zmx *.ZMX *.Zmx);;Text(*.txt));;all(*.*)");
    qDebug() << "filename:" << filePathName << endl;
    if (filePathName == NULL) {
        cout << "Please enter the file name to open!!!" << endl;
        ui->textEdit->setText(QString("Please choose the file you want to open."));
        string strPathName = Project1.sampleDir + "/LENS.ZMX";
        PathName = strPathName;
        return "NULL";
    }
    else {
        //1��zemax��̨�򿪳���
        PathName = filePathName.toStdString().c_str();
        ui->textEdit->setText(QString("Open successfully!"));
    }

    //�ԡ�/���͡�.��Ϊ�ָ�����ȡ�ļ�����
    vector<string> pnsplit = Project1.split(PathName, "/");
    vector<string> nsplit = Project1.split(pnsplit.back(), ".");
    transform(nsplit.back().begin(), nsplit.back().end(), nsplit.back().begin(), ::tolower);

    if (nsplit.back() != "zmx") {
        ui->textEdit->setText(QString("The open file is not ZMX file, please select again."));
        inputandverifythefile();
    }
    Project1.file_name = nsplit.front().c_str();
    return PathName;
}

vector<string> readfile(string filename) {
    vector<string> lines;
    string line;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
            << filename << "'" << endl;
    }

    while (getline(input_file, line)) {
        lines.push_back(line);
    }

    for (auto& i : lines)
        cout << i << endl;

    input_file.close();
    return lines;
}

//�رչ��̣����رս���
void zemaxqt::close_slot() {
    // Clean up�رձ���Ӧ�á��趨�رյ������������ó���һֱ���ڽ����źŲ���ʱ���г������״̬��
    Project1.finishStandaloneApplication();
    this->close();
    qDebug() << "successful!" << endl;
}



//�����̵߳ȴ��ӽ�����ɵ���Ϣ��
int waitsubprocessfinish(vector<ANYData> params) {
    //�Ե�������ʽ������еĽ��չʾ��MessageBox���������ĵ�����

    STARTUPINFO si;//�ڲ����ӽ���ʱ���ӽ��̵Ĵ��������Ϣ
    ::ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOWNORMAL;
    PROCESS_INFORMATION pi;                  //�ӽ��̵�ID/�߳������Ϣ
    DWORD returnCode;//���ڱ����ӳ̽��ķ���ֵ;
    //�������ȡ��������exe���ļ�·����    //�ҵ���Ӧ��Ŀ¼�鵽exe�ļ���

    //string exepath = "E:\\VSProject\\CppStandaloneApplication\\x64\\Release\\CppStandaloneApplication.exe";
    char exeFilePath[MAX_PATH + 1] = { 0 };
    GetModuleFileNameA(NULL, exeFilePath, MAX_PATH);
    string exepath = exeFilePath;
    TCHAR exePath[MAX_PATH];
#ifdef UNICODE
    _stprintf_s(exePath, MAX_PATH, _T("%S"), exepath.c_str());//%S���ַ�
#else
    _stprintf_s(exePath, MAX_PATH, _T("%s"), exepath.c_str());//%s���ַ�
#endif

    //�����б���
    //string cmdline = "background \"C:\\Users\\admin\\Documents\\Zemax\\Samples\\Sequential\\Objectives\\Cooke 40 degree field.zmx\" 60 0.1 0.9 60 0.0 20.00 0 0.0 0.0 1 0 0 0 0";
    //unsigned int WL_NUM = 31;    double WL_MIN = 0.400;    double WL_MAX = 0.700;
    //unsigned int IMGHT_NUM = 91; double IMGHT_MIN = 0.0; double IMGHT_MAX = 20.0;
    //unsigned int IMGWT_NUM = 0; double IMGWT_MIN = 0.0; double IMGWT_MAX = 0.0;
    //bool checkDistortionMultiple, checkChiefRayAngleMultiple, checkRelativeIlluminationMultiple,
    //    checkFFTPSFMultiple, checkHuygensPSFMultiple;
    //int Dis_whichwave, Dis_Fieldtypeindex, Dis_Distortiontype, Dis_Scantype;
    //int CRA_whichwave, CRA_direction;
    //int RI_whichwave, RI_direction;
    //int FFT_whichwave, FFT_Fieldtypeindex, FFT_Scantype, FFT_sampling, FFT_display, FFT_type, FFT_normalize;double FFT_imagedelta; 
    //int Huygens_whichwave, Huygens_Fieldtypeindex, Huygens_Scantype, Huygens_sampling, Huygens_display, Huygens_type,Huygens_normalize;double  Huygens_imagedelta;
    //int rayaming;

    string zmxpath = "\"" + PathName + "\"";
    unsigned int wlnumber = params[0].uival; double wlmin = params[1].dval; double wlmax = params[2].dval;
    unsigned int imhtnumber = params[3].uival; double imhtmin = params[4].dval; double imhtmax = params[5].dval;
    string cmdline = "background " + zmxpath + " " + to_string(wlnumber) + " " + to_string(wlmin) + " " + to_string(wlmax) + " "
        + to_string(imhtnumber) + " " + to_string(imhtmin) + " " + to_string(imhtmax) + " "
        + "0 0 0 "//���ǹ���imagewidth�ġ�
        + to_string(checkDistortionMultiple) +"_"+to_string(Dis_whichwave)+"_" + to_string(Dis_Fieldtypeindex) + "_" + to_string(Dis_Distortiontype) + "_" + to_string(Dis_Scantype) + " "
        + to_string(checkChiefRayAngleMultiple) + "_" + to_string(CRA_whichwave) + "_" + to_string(CRA_direction) + " "
        + to_string(checkRelativeIlluminationMultiple) + "_" + to_string(RI_whichwave) + "_" + to_string(RI_direction) + " "
        + to_string(checkFFTPSFMultiple) + "_" + to_string(FFT_whichwave) + "_" + to_string(FFT_Fieldtypeindex) + "_" + to_string(FFT_Scantype) + "_" + to_string(FFT_sampling) + "_" + to_string(FFT_display) + "_" + to_string(FFT_type) + "_" + to_string(FFT_imagedelta) + "_" + to_string(FFT_normalize) + " "
        + to_string(checkHuygensPSFMultiple) + "_" + to_string(Huygens_whichwave) + "_" + to_string(Huygens_Fieldtypeindex) + "_" + to_string(Huygens_Scantype) + "_" + to_string(Huygens_sampling) + "_" + to_string(Huygens_display) + "_" + to_string(Huygens_type) + "_" + to_string(Huygens_imagedelta) + "_" + to_string(Huygens_normalize) + " "
        + to_string(rayaming);
    TCHAR CmdLine[MAX_PATH];
#ifdef UNICODE
    _stprintf_s(CmdLine, MAX_PATH, TEXT("%S"), cmdline.c_str());//%S���ַ�
#else
    _stprintf_s(CmdLine, MAX_PATH, TEXT("%s"), cmdline.c_str);//%s���ַ�
#endif

    std::cout << "exePath:::" << exePath << endl;
    std::cout << "CmdLine:::" << CmdLine << endl;

    // Start the child process. 
    if (CreateProcess(
        exePath,   //exe·��
        CmdLine,   // Command line��Ӧ���ֲ���
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        CREATE_NEW_CONSOLE,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        time_t start, end;
        start = clock();
        //�趨���ļ���ȫ�ֱ���dwPid��returncode�����ſ�ʼ�ͽ������ı䡣
        std::cout << "process is running..." << std::endl;
        dwPid = GetProcessId(pi.hProcess);         //�������ʾ���̿�ʼ
        std::cout << "dwPid::" << dwPid << endl;
        //�ȴ��ӽ��̽���
        WaitForSingleObject(pi.hProcess, -1);
        std::cout << "process is finished" << std::endl;
        //��ȡ�ӽ��̵ķ���ֵ
        GetExitCodeProcess(pi.hProcess, &returnCode);
        std::cout << "process return code:" << returnCode << std::endl;
        returncode = returnCode;
        dwPid = -1;                                  //�������ʾ���̽���
        emit subweight.dwPidchangeSignal(dwPid);
        if (returncode == 0) {
            MessageBox(0, L"�����ж�", L"״̬", 0);
        }
        else {
            end = clock();
            double cost = (double)(end - start) / CLOCKS_PER_SEC;
            //CString msg;
            //msg.Format(_T("�ܺ�ʱ:%lf\n"), cost);
            //MessageBox(0, msg, _T("״̬"), MB_OK | MB_ICONWARNING);
        }
        return returnCode;
    }
    else
    {
        returncode = 0;
        MessageBox(0, L"û�п�������", L"û�п�������", 0);
        std::cout << "Create Process error!" << std::endl;
        return 0;
    }
}

#include "tlhelp32.h"
bool ListenExitProcesses(DWORD cur_pid)
{
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cout << "CreateToolhelp32Snapshot Error!" << endl;;
        return false;
    }

    BOOL bResult = Process32First(hProcessSnap, &pe32);
    BOOL bContinue = true; //Ϊfalse���˳�
    bool bRe = true;
    while (bContinue)
    {
        bRe = true;
        //��Ҫ���»�ȡ����id
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        bResult = Process32First(hProcessSnap, &pe32);  //������һ��
        while (bResult)
        {
            int id = pe32.th32ProcessID;
            if (id == cur_pid)
            {
                bResult = false;
                bRe = false;
                break;
            }
            bResult = Process32Next(hProcessSnap, &pe32);
        }
        if (bRe == true)
        {
            MessageBox(0, L"�����˳�", L"�����˳�", 0);
            //break;
            bContinue = false;
            break;
        }
    }
    CloseHandle(hProcessSnap);

    return true;
}

int KillProcess(int id)   //���ݽ���IDɱ����
{
    HANDLE hProcess = NULL;
    hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, id);	//��Ŀ�����
    if (hProcess == NULL) {
        wprintf(L"\nOpen Process fAiled:%d\n", GetLastError());
        return -1;
    }
    DWORD ret = TerminateProcess(hProcess, 0);	//����Ŀ�����
    if (ret == 0) {
        wprintf(L"%d", GetLastError());
    }
    CloseHandle(hProcess);
    return 1;
}
//����ʱ�����ı��ķ�ʽ��¼��txt�С�ͨ�����ϵĶԸ��ı����ж�ȡ��ö�Ӧ��Ŀ��ʱ�����ѡ�
//��Ҫ�����̼߳�ؽ��̵�����������ɺ�ᵯ����
void processfinish(int pid) {
    ListenExitProcesses(pid);
    dwPid = -1;
}
