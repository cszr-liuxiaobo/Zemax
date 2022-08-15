#pragma once
#include "stdafx.h"
//#include <QtCore/QCoreApplication>
//#include <QtWidgets/QMainWindow>
//#include <QtWidgets/qspinbox.h>
#include "basesetting.h"

using namespace std;

class zemaxqt : public QMainWindow,public ZemaxProject
{
    Q_OBJECT

public:
    zemaxqt(QWidget* parent = Q_NULLPTR);
    //~zemaxqt();
    QTimer* timSend;

    ZemaxProject Project1;
    vector<AnyData>  params_setting;
    //unsigned int WL_NUM;
    //double WL_MIN;
    //double WL_MAX;
    //unsigned int IMGHT_NUM;
    //double IMGHT_MIN;
    //double IMGHT_MAX;
    bool reporttap_flag, DistoritionTab_flag;
    QTimer* m_pTimer; QProgressBar* m_pProgressBar;
    QTextEdit* tab_report; int reporttabindex; 
    QWidget* tab_DistoritionTab;int actionDistoritiontabindex;
    QLabel* labelImageHeight; QPushButton* DistoritionButton;
    QString ImageHeightchange;
    QString ImageWidthchange;
    QSpinBox* spinBoxWavelengthNumber;
    int WavelengthNumber;
    double WLTchange, fieldY, fieldX;
    int RayAimingIndex;
    int fieldtypecurrentIndex, ScanTypecurrentIndex;
    QString scantype;
    //double distoritiondatachg[2];
    QTextEdit* textEditResult;

    QComboBox* ComboBoxFieldType;
    QLineEdit* lineEditlabelImageHeight;
    QLineEdit* lineEditlabelImageWidth;
    QLineEdit* lineWaveLengthValue;
    QComboBox* ComboBoxScanType;
    int checkDistortionMultipleflag, checkChiefRayAngleMultipleflag, checkRelativeIlluminationMultipleflag, checkFFTPSFMultipleflag, checkHuygensPSFMultipleflag;

    void MakeYourSetting(); void Tab0Setting();  void WavelengthFieldSetting(); void ExploreSetting(); void TasksRunningSetting(); void TasksRelatedSetting();
    string inputandverifythefile();
    void buildDock(zemaxqt* zemaxmainwidow);
    void buildReportTab(zemaxqt* zemaxmainwidow);
    //distoritionע��connectֻ�ܱ�����һ�Σ������Ҫ�����µľ���Ҫ���ɵ����٣����������ڽ����ϣ�����ͻ�����ظ����ź�����¼���
    void buildDistoritionTab(zemaxqt* zemaxmainwidow); void buildDistoritionTabConnects(zemaxqt* zemaxmainwidow);
    bool eventFilter(QObject* target, QEvent* event);
    void taskScheduleappendix(int a_process_ij, int a_totalnumber, int a_normal100, char* flag);

public slots:
    void openfile_slot();
    void Reports_slot();
    void close_slot();
    void on_openSrcDirPushButton_clicked();

    void Distorition_slot();
    void FieldHTNumberverify();
    void FieldHTMaxverify();
    void FieldHTMinverify();
    void AllFieldtypeverifyandFieldHTMaxChange();

    void WavelengthNumberverify(); 
    void WavelengthMaxverify();
    void WavelengthMinverify();
    void AllSamplingsizeverify();
    void AllDisplaysizeverify();
    void AllImageDeltaverify();
    void dwPidchangeSlot(int x);
    void TasksScheduleSlot();

    void closeTabSlot(int index);
    void WavelengthChangeSlot();
    void DistortionChangeSlot();
    void ImageHeightWidthChangeSlot();



signals:
    /*�źű����йؼ���signal����
     * �ź�û�з���ֵ�������в���
     * �źž��Ǻ�����������ֻ�����������趨��
     * emit mySignal();
     * �ź������ı����������ء�
*/
    //����signal�ı���������Ŀ,���Խ����µ�class����ֱ������ʵ������class
    //void dwPidchangeSignal(int);
private:
    Ui::MainWindow *ui;
};

//����signal�ı���������Ŀ
class zemaxqt_subweight : public QObject   //ֻ��Qt����ܶ����ź�
{
    Q_OBJECT    //����ʹ�ú�Q_OBJECT
public:
    //void send(int i)
    //{
    //    emit dwPidchangeSignal(i);     //ͨ��emit�ؼ��ַ����ź�
    //}
signals:                    //ʹ��signals�����źź��������ʼ���Ϊprotected
    void dwPidchangeSignal(int v);     //�ź�ֻ���������ܶ���
    //void sendFFTPSFSignal(int v);
};