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
    //distorition注意connect只能被建立一次，如果需要建立新的就需要将旧的销毁，不可体现在界面上，否则就会出现重复的信号与槽事件。
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
    /*信号必须有关键字signal声明
     * 信号没有返回值，可以有参数
     * 信号就是函数的声明，只需声明，无需定义
     * emit mySignal();
     * 信号声明的变量可以重载。
*/
    //发射signal的必须是子项目,可以建立新的class或者直接重新实例化被class
    //void dwPidchangeSignal(int);
private:
    Ui::MainWindow *ui;
};

//发射signal的必须是子项目
class zemaxqt_subweight : public QObject   //只有Qt类才能定义信号
{
    Q_OBJECT    //必须使用宏Q_OBJECT
public:
    //void send(int i)
    //{
    //    emit dwPidchangeSignal(i);     //通过emit关键字发射信号
    //}
signals:                    //使用signals声明信号函数，访问级别为protected
    void dwPidchangeSignal(int v);     //信号只能声明不能定义
    //void sendFFTPSFSignal(int v);
};