/********************************************************************************
** Form generated from reading UI file 'zemaxqt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZEMAXQT_H
#define UI_ZEMAXQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionopen;
    QAction *actionclose;
    QAction *Reports;
    QAction *actionDistorition;
    QAction *actionChiefRayAngle;
    QAction *actionRelativeIllumination;
    QAction *actionDistoritionMultiple;
    QAction *actionChiefRayAngleMultiple;
    QAction *actionRelativeIlluminationMultiple;
    QAction *actionFFTPSFMultiple;
    QAction *actionHuygensPSFMultiple;
    QAction *actionFFTPSF;
    QAction *actionHuygensPSF;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *YourSetting;
    QToolBox *toolBox;
    QWidget *pageFields;
    QFormLayout *formLayout_3;
    QLabel *labelFieldHTNumber;
    QLineEdit *lineEditFieldHTNumber;
    QLabel *labelFieldHTMin;
    QLineEdit *lineEditFieldHTMin;
    QLabel *labelFieldHTMax;
    QLineEdit *lineEditFieldHTMax;
    QLabel *labelallFieldtype;
    QComboBox *comboBoxAllFieldtype;
    QWidget *pageWavelengths;
    QFormLayout *formLayout_2;
    QLabel *labelWaveNumber;
    QLineEdit *lineEditWavelengthNumber;
    QLabel *labelWaveMin;
    QLineEdit *lineEditWavelengthMin;
    QLabel *labelWaveMax;
    QLineEdit *lineEditWavelengthMax;
    QWidget *pageRayAming;
    QComboBox *comboBoxRayAiming;
    QWidget *pageTaskRunning;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *labelAllSampling;
    QComboBox *comboBoxAllSampling;
    QLabel *labelAllDisplay;
    QComboBox *comboBoxAllDisplay;
    QLabel *labelAllImageDelta;
    QLineEdit *lineEditAllImageDelta;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonRunning;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonCanceling;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton_FFTPSFMultiple;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *radioButton_HuygensPSFMultiple;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBoxDistortionMultiple;
    QCheckBox *checkBoxChiefRayAngleMultiple;
    QCheckBox *checkBoxRelativeIlluminationMultiple;
    QCheckBox *checkBoxFFTPSFMultiple;
    QCheckBox *checkBoxHuygensPSFMultiple;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *lineEdit_outputpath;
    QPushButton *pushButton_outputpath;
    QTabWidget *tabWidget;
    QWidget *tab_0;
    QHBoxLayout *horizontalLayout_0;
    QTextEdit *textEdit_tab0;
    QWidget *tab;
    QGroupBox *groupBox1DMRelatedSetting;
    QLabel *labelWhichwave;
    QLineEdit *lineEditWhichwave;
    QLabel *labelFieldtype;
    QLabel *labelDistortiontype;
    QLabel *labelScantype;
    QComboBox *comboBoxFieldtype;
    QComboBox *comboBoxScantype;
    QComboBox *comboBoxDistortiontype;
    QGroupBox *groupBox2CRARelatedSetting;
    QLabel *labelWhichwave_2;
    QLineEdit *lineEditWhichwave_2;
    QLabel *labelDirection_2;
    QComboBox *comboDirection_2;
    QGroupBox *groupBox3RIRelatedSetting;
    QLabel *labelWhichwave_3;
    QLineEdit *lineEditWhichwave_3;
    QComboBox *comboDirection_3;
    QLabel *labelDirection_3;
    QGroupBox *groupBox4FFTPSFRelatedSetting;
    QLabel *labelWhichwave_4;
    QLineEdit *lineEditWhichwave_4;
    QLabel *labelFieldtype_4;
    QLabel *labelSampling_4;
    QLabel *labelScantype_4;
    QComboBox *comboBoxFieldtype_4;
    QComboBox *comboBoxScantype_4;
    QComboBox *comboBoxSampling_4;
    QLabel *labelDisplay_4;
    QLineEdit *lineEditImageDelta_4;
    QLabel *labelImageDelta_4;
    QComboBox *comboBoxType_4;
    QLabel *labelType_4;
    QCheckBox *checkBoxNormalize_4;
    QComboBox *comboBoxDisplay_4;
    QGroupBox *groupBox5HuygensPSFRelatedSetting;
    QLabel *labelWhichwave_5;
    QLineEdit *lineEditWhichwave_5;
    QLabel *labelFieldtype_5;
    QLabel *labelSampling_5;
    QLabel *labelScantype_5;
    QComboBox *comboBoxFieldtype_5;
    QComboBox *comboBoxScantype_5;
    QComboBox *comboBoxSampling_5;
    QLabel *labelDisplay_5;
    QLineEdit *lineEditImageDelta_5;
    QLabel *labelImageDelta_5;
    QComboBox *comboBoxType_5;
    QLabel *labelType_5;
    QCheckBox *checkBoxNormalize_5;
    QComboBox *comboBoxDisplay_5;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAnalyse;
    QMenu *menuPFS;
    QMenu *menuDistorition;
    QMenu *menuChiefRayAngle;
    QMenu *menuRelativeIllumination;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1314, 887);
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName(QStringLiteral("actionopen"));
        actionclose = new QAction(MainWindow);
        actionclose->setObjectName(QStringLiteral("actionclose"));
        Reports = new QAction(MainWindow);
        Reports->setObjectName(QStringLiteral("Reports"));
        actionDistorition = new QAction(MainWindow);
        actionDistorition->setObjectName(QStringLiteral("actionDistorition"));
        actionChiefRayAngle = new QAction(MainWindow);
        actionChiefRayAngle->setObjectName(QStringLiteral("actionChiefRayAngle"));
        actionRelativeIllumination = new QAction(MainWindow);
        actionRelativeIllumination->setObjectName(QStringLiteral("actionRelativeIllumination"));
        actionDistoritionMultiple = new QAction(MainWindow);
        actionDistoritionMultiple->setObjectName(QStringLiteral("actionDistoritionMultiple"));
        actionChiefRayAngleMultiple = new QAction(MainWindow);
        actionChiefRayAngleMultiple->setObjectName(QStringLiteral("actionChiefRayAngleMultiple"));
        actionRelativeIlluminationMultiple = new QAction(MainWindow);
        actionRelativeIlluminationMultiple->setObjectName(QStringLiteral("actionRelativeIlluminationMultiple"));
        actionFFTPSFMultiple = new QAction(MainWindow);
        actionFFTPSFMultiple->setObjectName(QStringLiteral("actionFFTPSFMultiple"));
        actionHuygensPSFMultiple = new QAction(MainWindow);
        actionHuygensPSFMultiple->setObjectName(QStringLiteral("actionHuygensPSFMultiple"));
        actionFFTPSF = new QAction(MainWindow);
        actionFFTPSF->setObjectName(QStringLiteral("actionFFTPSF"));
        actionHuygensPSF = new QAction(MainWindow);
        actionHuygensPSF->setObjectName(QStringLiteral("actionHuygensPSF"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 10, -1, -1);
        YourSetting = new QLabel(centralwidget);
        YourSetting->setObjectName(QStringLiteral("YourSetting"));

        verticalLayout->addWidget(YourSetting);

        toolBox = new QToolBox(centralwidget);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setMinimumSize(QSize(280, 300));
        toolBox->setMaximumSize(QSize(210, 16777215));
        toolBox->setAutoFillBackground(true);
        pageFields = new QWidget();
        pageFields->setObjectName(QStringLiteral("pageFields"));
        pageFields->setGeometry(QRect(0, 0, 280, 503));
        formLayout_3 = new QFormLayout(pageFields);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        labelFieldHTNumber = new QLabel(pageFields);
        labelFieldHTNumber->setObjectName(QStringLiteral("labelFieldHTNumber"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, labelFieldHTNumber);

        lineEditFieldHTNumber = new QLineEdit(pageFields);
        lineEditFieldHTNumber->setObjectName(QStringLiteral("lineEditFieldHTNumber"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, lineEditFieldHTNumber);

        labelFieldHTMin = new QLabel(pageFields);
        labelFieldHTMin->setObjectName(QStringLiteral("labelFieldHTMin"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, labelFieldHTMin);

        lineEditFieldHTMin = new QLineEdit(pageFields);
        lineEditFieldHTMin->setObjectName(QStringLiteral("lineEditFieldHTMin"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, lineEditFieldHTMin);

        labelFieldHTMax = new QLabel(pageFields);
        labelFieldHTMax->setObjectName(QStringLiteral("labelFieldHTMax"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, labelFieldHTMax);

        lineEditFieldHTMax = new QLineEdit(pageFields);
        lineEditFieldHTMax->setObjectName(QStringLiteral("lineEditFieldHTMax"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, lineEditFieldHTMax);

        labelallFieldtype = new QLabel(pageFields);
        labelallFieldtype->setObjectName(QStringLiteral("labelallFieldtype"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, labelallFieldtype);

        comboBoxAllFieldtype = new QComboBox(pageFields);
        comboBoxAllFieldtype->setObjectName(QStringLiteral("comboBoxAllFieldtype"));
        comboBoxAllFieldtype->setEnabled(true);
        comboBoxAllFieldtype->setMaxVisibleItems(11);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, comboBoxAllFieldtype);

        toolBox->addItem(pageFields, QStringLiteral("Fields"));
        pageWavelengths = new QWidget();
        pageWavelengths->setObjectName(QStringLiteral("pageWavelengths"));
        pageWavelengths->setGeometry(QRect(0, 0, 280, 503));
        formLayout_2 = new QFormLayout(pageWavelengths);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        labelWaveNumber = new QLabel(pageWavelengths);
        labelWaveNumber->setObjectName(QStringLiteral("labelWaveNumber"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, labelWaveNumber);

        lineEditWavelengthNumber = new QLineEdit(pageWavelengths);
        lineEditWavelengthNumber->setObjectName(QStringLiteral("lineEditWavelengthNumber"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEditWavelengthNumber);

        labelWaveMin = new QLabel(pageWavelengths);
        labelWaveMin->setObjectName(QStringLiteral("labelWaveMin"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, labelWaveMin);

        lineEditWavelengthMin = new QLineEdit(pageWavelengths);
        lineEditWavelengthMin->setObjectName(QStringLiteral("lineEditWavelengthMin"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEditWavelengthMin);

        labelWaveMax = new QLabel(pageWavelengths);
        labelWaveMax->setObjectName(QStringLiteral("labelWaveMax"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, labelWaveMax);

        lineEditWavelengthMax = new QLineEdit(pageWavelengths);
        lineEditWavelengthMax->setObjectName(QStringLiteral("lineEditWavelengthMax"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lineEditWavelengthMax);

        toolBox->addItem(pageWavelengths, QStringLiteral("Wavelengths"));
        pageRayAming = new QWidget();
        pageRayAming->setObjectName(QStringLiteral("pageRayAming"));
        pageRayAming->setGeometry(QRect(0, 0, 280, 503));
        comboBoxRayAiming = new QComboBox(pageRayAming);
        comboBoxRayAiming->setObjectName(QStringLiteral("comboBoxRayAiming"));
        comboBoxRayAiming->setGeometry(QRect(70, 0, 201, 30));
        toolBox->addItem(pageRayAming, QStringLiteral("RayAming"));
        pageTaskRunning = new QWidget();
        pageTaskRunning->setObjectName(QStringLiteral("pageTaskRunning"));
        pageTaskRunning->setGeometry(QRect(0, 0, 280, 503));
        layoutWidget = new QWidget(pageTaskRunning);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 261, 76));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        labelAllSampling = new QLabel(layoutWidget);
        labelAllSampling->setObjectName(QStringLiteral("labelAllSampling"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelAllSampling);

        comboBoxAllSampling = new QComboBox(layoutWidget);
        comboBoxAllSampling->setObjectName(QStringLiteral("comboBoxAllSampling"));
        comboBoxAllSampling->setEnabled(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBoxAllSampling);

        labelAllDisplay = new QLabel(layoutWidget);
        labelAllDisplay->setObjectName(QStringLiteral("labelAllDisplay"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelAllDisplay);

        comboBoxAllDisplay = new QComboBox(layoutWidget);
        comboBoxAllDisplay->setObjectName(QStringLiteral("comboBoxAllDisplay"));
        comboBoxAllDisplay->setEnabled(true);
        comboBoxAllDisplay->setEditable(false);
        comboBoxAllDisplay->setMaxVisibleItems(10);
        comboBoxAllDisplay->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBoxAllDisplay);

        labelAllImageDelta = new QLabel(layoutWidget);
        labelAllImageDelta->setObjectName(QStringLiteral("labelAllImageDelta"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelAllImageDelta);

        lineEditAllImageDelta = new QLineEdit(layoutWidget);
        lineEditAllImageDelta->setObjectName(QStringLiteral("lineEditAllImageDelta"));
        lineEditAllImageDelta->setEnabled(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditAllImageDelta);

        layoutWidget1 = new QWidget(pageTaskRunning);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 130, 232, 25));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButtonRunning = new QPushButton(layoutWidget1);
        pushButtonRunning->setObjectName(QStringLiteral("pushButtonRunning"));

        horizontalLayout_4->addWidget(pushButtonRunning);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButtonCanceling = new QPushButton(layoutWidget1);
        pushButtonCanceling->setObjectName(QStringLiteral("pushButtonCanceling"));

        horizontalLayout_4->addWidget(pushButtonCanceling);

        layoutWidget2 = new QWidget(pageTaskRunning);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(31, 100, 214, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        radioButton_FFTPSFMultiple = new QRadioButton(layoutWidget2);
        radioButton_FFTPSFMultiple->setObjectName(QStringLiteral("radioButton_FFTPSFMultiple"));

        horizontalLayout_3->addWidget(radioButton_FFTPSFMultiple);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        radioButton_HuygensPSFMultiple = new QRadioButton(layoutWidget2);
        radioButton_HuygensPSFMultiple->setObjectName(QStringLiteral("radioButton_HuygensPSFMultiple"));

        horizontalLayout_3->addWidget(radioButton_HuygensPSFMultiple);

        layoutWidget3 = new QWidget(pageTaskRunning);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(20, 260, 193, 106));
        verticalLayout_3 = new QVBoxLayout(layoutWidget3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        checkBoxDistortionMultiple = new QCheckBox(layoutWidget3);
        checkBoxDistortionMultiple->setObjectName(QStringLiteral("checkBoxDistortionMultiple"));
        checkBoxDistortionMultiple->setChecked(true);

        verticalLayout_3->addWidget(checkBoxDistortionMultiple);

        checkBoxChiefRayAngleMultiple = new QCheckBox(layoutWidget3);
        checkBoxChiefRayAngleMultiple->setObjectName(QStringLiteral("checkBoxChiefRayAngleMultiple"));
        checkBoxChiefRayAngleMultiple->setChecked(true);

        verticalLayout_3->addWidget(checkBoxChiefRayAngleMultiple);

        checkBoxRelativeIlluminationMultiple = new QCheckBox(layoutWidget3);
        checkBoxRelativeIlluminationMultiple->setObjectName(QStringLiteral("checkBoxRelativeIlluminationMultiple"));
        checkBoxRelativeIlluminationMultiple->setChecked(true);

        verticalLayout_3->addWidget(checkBoxRelativeIlluminationMultiple);

        checkBoxFFTPSFMultiple = new QCheckBox(layoutWidget3);
        checkBoxFFTPSFMultiple->setObjectName(QStringLiteral("checkBoxFFTPSFMultiple"));
        checkBoxFFTPSFMultiple->setChecked(false);

        verticalLayout_3->addWidget(checkBoxFFTPSFMultiple);

        checkBoxHuygensPSFMultiple = new QCheckBox(layoutWidget3);
        checkBoxHuygensPSFMultiple->setObjectName(QStringLiteral("checkBoxHuygensPSFMultiple"));
        checkBoxHuygensPSFMultiple->setChecked(false);

        verticalLayout_3->addWidget(checkBoxHuygensPSFMultiple);

        layoutWidget4 = new QWidget(pageTaskRunning);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 190, 261, 25));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        lineEdit_outputpath = new QLineEdit(layoutWidget4);
        lineEdit_outputpath->setObjectName(QStringLiteral("lineEdit_outputpath"));
        lineEdit_outputpath->setReadOnly(true);

        horizontalLayout_5->addWidget(lineEdit_outputpath);

        pushButton_outputpath = new QPushButton(layoutWidget4);
        pushButton_outputpath->setObjectName(QStringLiteral("pushButton_outputpath"));

        horizontalLayout_5->addWidget(pushButton_outputpath);

        toolBox->addItem(pageTaskRunning, QStringLiteral("TaskRunning"));

        verticalLayout->addWidget(toolBox);


        horizontalLayout->addLayout(verticalLayout);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setAutoFillBackground(true);
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(false);
        tab_0 = new QWidget();
        tab_0->setObjectName(QStringLiteral("tab_0"));
        tab_0->setEnabled(true);
        tab_0->setInputMethodHints(Qt::ImhNone);
        horizontalLayout_0 = new QHBoxLayout(tab_0);
        horizontalLayout_0->setObjectName(QStringLiteral("horizontalLayout_0"));
        textEdit_tab0 = new QTextEdit(tab_0);
        textEdit_tab0->setObjectName(QStringLiteral("textEdit_tab0"));

        horizontalLayout_0->addWidget(textEdit_tab0);

        tabWidget->addTab(tab_0, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tab->setEnabled(true);
        groupBox1DMRelatedSetting = new QGroupBox(tab);
        groupBox1DMRelatedSetting->setObjectName(QStringLiteral("groupBox1DMRelatedSetting"));
        groupBox1DMRelatedSetting->setGeometry(QRect(0, 0, 641, 81));
        labelWhichwave = new QLabel(groupBox1DMRelatedSetting);
        labelWhichwave->setObjectName(QStringLiteral("labelWhichwave"));
        labelWhichwave->setGeometry(QRect(10, 20, 111, 16));
        lineEditWhichwave = new QLineEdit(groupBox1DMRelatedSetting);
        lineEditWhichwave->setObjectName(QStringLiteral("lineEditWhichwave"));
        lineEditWhichwave->setEnabled(false);
        lineEditWhichwave->setGeometry(QRect(110, 20, 113, 20));
        labelFieldtype = new QLabel(groupBox1DMRelatedSetting);
        labelFieldtype->setObjectName(QStringLiteral("labelFieldtype"));
        labelFieldtype->setGeometry(QRect(270, 20, 111, 16));
        labelDistortiontype = new QLabel(groupBox1DMRelatedSetting);
        labelDistortiontype->setObjectName(QStringLiteral("labelDistortiontype"));
        labelDistortiontype->setGeometry(QRect(10, 50, 111, 16));
        labelScantype = new QLabel(groupBox1DMRelatedSetting);
        labelScantype->setObjectName(QStringLiteral("labelScantype"));
        labelScantype->setGeometry(QRect(270, 50, 111, 16));
        comboBoxFieldtype = new QComboBox(groupBox1DMRelatedSetting);
        comboBoxFieldtype->setObjectName(QStringLiteral("comboBoxFieldtype"));
        comboBoxFieldtype->setEnabled(true);
        comboBoxFieldtype->setGeometry(QRect(350, 20, 111, 22));
        comboBoxScantype = new QComboBox(groupBox1DMRelatedSetting);
        comboBoxScantype->setObjectName(QStringLiteral("comboBoxScantype"));
        comboBoxScantype->setEnabled(false);
        comboBoxScantype->setGeometry(QRect(350, 50, 111, 22));
        comboBoxDistortiontype = new QComboBox(groupBox1DMRelatedSetting);
        comboBoxDistortiontype->setObjectName(QStringLiteral("comboBoxDistortiontype"));
        comboBoxDistortiontype->setEnabled(true);
        comboBoxDistortiontype->setGeometry(QRect(110, 50, 111, 22));
        groupBox2CRARelatedSetting = new QGroupBox(tab);
        groupBox2CRARelatedSetting->setObjectName(QStringLiteral("groupBox2CRARelatedSetting"));
        groupBox2CRARelatedSetting->setGeometry(QRect(0, 90, 641, 51));
        labelWhichwave_2 = new QLabel(groupBox2CRARelatedSetting);
        labelWhichwave_2->setObjectName(QStringLiteral("labelWhichwave_2"));
        labelWhichwave_2->setGeometry(QRect(10, 20, 111, 16));
        lineEditWhichwave_2 = new QLineEdit(groupBox2CRARelatedSetting);
        lineEditWhichwave_2->setObjectName(QStringLiteral("lineEditWhichwave_2"));
        lineEditWhichwave_2->setEnabled(false);
        lineEditWhichwave_2->setGeometry(QRect(110, 20, 113, 20));
        labelDirection_2 = new QLabel(groupBox2CRARelatedSetting);
        labelDirection_2->setObjectName(QStringLiteral("labelDirection_2"));
        labelDirection_2->setGeometry(QRect(270, 20, 111, 16));
        comboDirection_2 = new QComboBox(groupBox2CRARelatedSetting);
        comboDirection_2->setObjectName(QStringLiteral("comboDirection_2"));
        comboDirection_2->setEnabled(false);
        comboDirection_2->setGeometry(QRect(350, 20, 111, 22));
        groupBox3RIRelatedSetting = new QGroupBox(tab);
        groupBox3RIRelatedSetting->setObjectName(QStringLiteral("groupBox3RIRelatedSetting"));
        groupBox3RIRelatedSetting->setGeometry(QRect(0, 150, 641, 51));
        labelWhichwave_3 = new QLabel(groupBox3RIRelatedSetting);
        labelWhichwave_3->setObjectName(QStringLiteral("labelWhichwave_3"));
        labelWhichwave_3->setGeometry(QRect(10, 20, 111, 16));
        lineEditWhichwave_3 = new QLineEdit(groupBox3RIRelatedSetting);
        lineEditWhichwave_3->setObjectName(QStringLiteral("lineEditWhichwave_3"));
        lineEditWhichwave_3->setEnabled(false);
        lineEditWhichwave_3->setGeometry(QRect(110, 20, 113, 20));
        comboDirection_3 = new QComboBox(groupBox3RIRelatedSetting);
        comboDirection_3->setObjectName(QStringLiteral("comboDirection_3"));
        comboDirection_3->setEnabled(false);
        comboDirection_3->setGeometry(QRect(350, 20, 111, 22));
        labelDirection_3 = new QLabel(groupBox3RIRelatedSetting);
        labelDirection_3->setObjectName(QStringLiteral("labelDirection_3"));
        labelDirection_3->setGeometry(QRect(270, 20, 111, 16));
        groupBox4FFTPSFRelatedSetting = new QGroupBox(tab);
        groupBox4FFTPSFRelatedSetting->setObjectName(QStringLiteral("groupBox4FFTPSFRelatedSetting"));
        groupBox4FFTPSFRelatedSetting->setGeometry(QRect(0, 210, 641, 161));
        labelWhichwave_4 = new QLabel(groupBox4FFTPSFRelatedSetting);
        labelWhichwave_4->setObjectName(QStringLiteral("labelWhichwave_4"));
        labelWhichwave_4->setGeometry(QRect(10, 20, 111, 16));
        lineEditWhichwave_4 = new QLineEdit(groupBox4FFTPSFRelatedSetting);
        lineEditWhichwave_4->setObjectName(QStringLiteral("lineEditWhichwave_4"));
        lineEditWhichwave_4->setEnabled(false);
        lineEditWhichwave_4->setGeometry(QRect(110, 20, 113, 20));
        labelFieldtype_4 = new QLabel(groupBox4FFTPSFRelatedSetting);
        labelFieldtype_4->setObjectName(QStringLiteral("labelFieldtype_4"));
        labelFieldtype_4->setGeometry(QRect(270, 20, 111, 16));
        labelSampling_4 = new QLabel(groupBox4FFTPSFRelatedSetting);
        labelSampling_4->setObjectName(QStringLiteral("labelSampling_4"));
        labelSampling_4->setGeometry(QRect(10, 50, 111, 16));
        labelScantype_4 = new QLabel(groupBox4FFTPSFRelatedSetting);
        labelScantype_4->setObjectName(QStringLiteral("labelScantype_4"));
        labelScantype_4->setGeometry(QRect(270, 50, 111, 16));
        comboBoxFieldtype_4 = new QComboBox(groupBox4FFTPSFRelatedSetting);
        comboBoxFieldtype_4->setObjectName(QStringLiteral("comboBoxFieldtype_4"));
        comboBoxFieldtype_4->setEnabled(true);
        comboBoxFieldtype_4->setGeometry(QRect(350, 20, 111, 22));
        comboBoxScantype_4 = new QComboBox(groupBox4FFTPSFRelatedSetting);
        comboBoxScantype_4->setObjectName(QStringLiteral("comboBoxScantype_4"));
        comboBoxScantype_4->setEnabled(false);
        comboBoxScantype_4->setGeometry(QRect(350, 50, 111, 22));
        comboBoxSampling_4 = new QComboBox(groupBox4FFTPSFRelatedSetting);
        comboBoxSampling_4->setObjectName(QStringLiteral("comboBoxSampling_4"));
        comboBoxSampling_4->setEnabled(true);
        comboBoxSampling_4->setGeometry(QRect(110, 50, 111, 22));
        labelDisplay_4 = new QLabel(groupBox4FFTPSFRelatedSetting);
        labelDisplay_4->setObjectName(QStringLiteral("labelDisplay_4"));
        labelDisplay_4->setGeometry(QRect(10, 80, 111, 16));
        lineEditImageDelta_4 = new QLineEdit(groupBox4FFTPSFRelatedSetting);
        lineEditImageDelta_4->setObjectName(QStringLiteral("lineEditImageDelta_4"));
        lineEditImageDelta_4->setEnabled(false);
        lineEditImageDelta_4->setGeometry(QRect(110, 110, 113, 20));
        labelImageDelta_4 = new QLabel(groupBox4FFTPSFRelatedSetting);
        labelImageDelta_4->setObjectName(QStringLiteral("labelImageDelta_4"));
        labelImageDelta_4->setGeometry(QRect(10, 110, 111, 16));
        comboBoxType_4 = new QComboBox(groupBox4FFTPSFRelatedSetting);
        comboBoxType_4->setObjectName(QStringLiteral("comboBoxType_4"));
        comboBoxType_4->setEnabled(true);
        comboBoxType_4->setGeometry(QRect(350, 80, 111, 22));
        labelType_4 = new QLabel(groupBox4FFTPSFRelatedSetting);
        labelType_4->setObjectName(QStringLiteral("labelType_4"));
        labelType_4->setGeometry(QRect(270, 80, 111, 16));
        checkBoxNormalize_4 = new QCheckBox(groupBox4FFTPSFRelatedSetting);
        checkBoxNormalize_4->setObjectName(QStringLiteral("checkBoxNormalize_4"));
        checkBoxNormalize_4->setGeometry(QRect(270, 110, 191, 16));
        checkBoxNormalize_4->setChecked(false);
        comboBoxDisplay_4 = new QComboBox(groupBox4FFTPSFRelatedSetting);
        comboBoxDisplay_4->setObjectName(QStringLiteral("comboBoxDisplay_4"));
        comboBoxDisplay_4->setEnabled(true);
        comboBoxDisplay_4->setGeometry(QRect(110, 80, 111, 20));
        comboBoxDisplay_4->setEditable(false);
        comboBoxDisplay_4->setMaxVisibleItems(10);
        comboBoxDisplay_4->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
        groupBox5HuygensPSFRelatedSetting = new QGroupBox(tab);
        groupBox5HuygensPSFRelatedSetting->setObjectName(QStringLiteral("groupBox5HuygensPSFRelatedSetting"));
        groupBox5HuygensPSFRelatedSetting->setGeometry(QRect(0, 380, 641, 161));
        labelWhichwave_5 = new QLabel(groupBox5HuygensPSFRelatedSetting);
        labelWhichwave_5->setObjectName(QStringLiteral("labelWhichwave_5"));
        labelWhichwave_5->setGeometry(QRect(10, 20, 111, 16));
        lineEditWhichwave_5 = new QLineEdit(groupBox5HuygensPSFRelatedSetting);
        lineEditWhichwave_5->setObjectName(QStringLiteral("lineEditWhichwave_5"));
        lineEditWhichwave_5->setEnabled(false);
        lineEditWhichwave_5->setGeometry(QRect(110, 20, 113, 20));
        labelFieldtype_5 = new QLabel(groupBox5HuygensPSFRelatedSetting);
        labelFieldtype_5->setObjectName(QStringLiteral("labelFieldtype_5"));
        labelFieldtype_5->setGeometry(QRect(270, 20, 111, 16));
        labelSampling_5 = new QLabel(groupBox5HuygensPSFRelatedSetting);
        labelSampling_5->setObjectName(QStringLiteral("labelSampling_5"));
        labelSampling_5->setGeometry(QRect(10, 50, 111, 16));
        labelScantype_5 = new QLabel(groupBox5HuygensPSFRelatedSetting);
        labelScantype_5->setObjectName(QStringLiteral("labelScantype_5"));
        labelScantype_5->setGeometry(QRect(270, 50, 111, 16));
        comboBoxFieldtype_5 = new QComboBox(groupBox5HuygensPSFRelatedSetting);
        comboBoxFieldtype_5->setObjectName(QStringLiteral("comboBoxFieldtype_5"));
        comboBoxFieldtype_5->setEnabled(true);
        comboBoxFieldtype_5->setGeometry(QRect(350, 20, 111, 22));
        comboBoxScantype_5 = new QComboBox(groupBox5HuygensPSFRelatedSetting);
        comboBoxScantype_5->setObjectName(QStringLiteral("comboBoxScantype_5"));
        comboBoxScantype_5->setEnabled(false);
        comboBoxScantype_5->setGeometry(QRect(350, 50, 111, 22));
        comboBoxSampling_5 = new QComboBox(groupBox5HuygensPSFRelatedSetting);
        comboBoxSampling_5->setObjectName(QStringLiteral("comboBoxSampling_5"));
        comboBoxSampling_5->setEnabled(true);
        comboBoxSampling_5->setGeometry(QRect(110, 50, 111, 22));
        labelDisplay_5 = new QLabel(groupBox5HuygensPSFRelatedSetting);
        labelDisplay_5->setObjectName(QStringLiteral("labelDisplay_5"));
        labelDisplay_5->setGeometry(QRect(10, 80, 111, 16));
        lineEditImageDelta_5 = new QLineEdit(groupBox5HuygensPSFRelatedSetting);
        lineEditImageDelta_5->setObjectName(QStringLiteral("lineEditImageDelta_5"));
        lineEditImageDelta_5->setEnabled(false);
        lineEditImageDelta_5->setGeometry(QRect(110, 110, 113, 20));
        labelImageDelta_5 = new QLabel(groupBox5HuygensPSFRelatedSetting);
        labelImageDelta_5->setObjectName(QStringLiteral("labelImageDelta_5"));
        labelImageDelta_5->setGeometry(QRect(10, 110, 111, 16));
        comboBoxType_5 = new QComboBox(groupBox5HuygensPSFRelatedSetting);
        comboBoxType_5->setObjectName(QStringLiteral("comboBoxType_5"));
        comboBoxType_5->setEnabled(true);
        comboBoxType_5->setGeometry(QRect(350, 80, 111, 22));
        labelType_5 = new QLabel(groupBox5HuygensPSFRelatedSetting);
        labelType_5->setObjectName(QStringLiteral("labelType_5"));
        labelType_5->setGeometry(QRect(270, 80, 111, 16));
        checkBoxNormalize_5 = new QCheckBox(groupBox5HuygensPSFRelatedSetting);
        checkBoxNormalize_5->setObjectName(QStringLiteral("checkBoxNormalize_5"));
        checkBoxNormalize_5->setGeometry(QRect(270, 110, 191, 16));
        checkBoxNormalize_5->setChecked(false);
        comboBoxDisplay_5 = new QComboBox(groupBox5HuygensPSFRelatedSetting);
        comboBoxDisplay_5->setObjectName(QStringLiteral("comboBoxDisplay_5"));
        comboBoxDisplay_5->setEnabled(true);
        comboBoxDisplay_5->setGeometry(QRect(110, 80, 111, 22));
        tabWidget->addTab(tab, QString());

        horizontalLayout->addWidget(tabWidget);


        verticalLayout_2->addLayout(horizontalLayout);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(0, 50));
        textEdit->setMaximumSize(QSize(16777215, 200));
        textEdit->setReadOnly(true);

        verticalLayout_2->addWidget(textEdit);


        horizontalLayout_2->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1314, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAnalyse = new QMenu(menubar);
        menuAnalyse->setObjectName(QStringLiteral("menuAnalyse"));
        menuAnalyse->setToolTipsVisible(true);
        menuPFS = new QMenu(menuAnalyse);
        menuPFS->setObjectName(QStringLiteral("menuPFS"));
        menuDistorition = new QMenu(menuAnalyse);
        menuDistorition->setObjectName(QStringLiteral("menuDistorition"));
        menuChiefRayAngle = new QMenu(menuAnalyse);
        menuChiefRayAngle->setObjectName(QStringLiteral("menuChiefRayAngle"));
        menuRelativeIllumination = new QMenu(menuAnalyse);
        menuRelativeIllumination->setObjectName(QStringLiteral("menuRelativeIllumination"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAnalyse->menuAction());
        menuFile->addAction(actionopen);
        menuFile->addSeparator();
        menuFile->addAction(Reports);
        menuFile->addSeparator();
        menuFile->addAction(actionclose);
        menuAnalyse->addSeparator();
        menuAnalyse->addAction(menuDistorition->menuAction());
        menuAnalyse->addSeparator();
        menuAnalyse->addAction(menuChiefRayAngle->menuAction());
        menuAnalyse->addSeparator();
        menuAnalyse->addAction(menuRelativeIllumination->menuAction());
        menuAnalyse->addSeparator();
        menuAnalyse->addAction(menuPFS->menuAction());
        menuPFS->addAction(actionFFTPSF);
        menuPFS->addAction(actionFFTPSFMultiple);
        menuPFS->addAction(actionHuygensPSF);
        menuPFS->addAction(actionHuygensPSFMultiple);
        menuDistorition->addAction(actionDistorition);
        menuDistorition->addAction(actionDistoritionMultiple);
        menuChiefRayAngle->addAction(actionChiefRayAngle);
        menuChiefRayAngle->addAction(actionChiefRayAngleMultiple);
        menuRelativeIllumination->addAction(actionRelativeIllumination);
        menuRelativeIllumination->addAction(actionRelativeIlluminationMultiple);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(3);
        comboBoxRayAiming->setCurrentIndex(2);
        comboBoxAllDisplay->setCurrentIndex(0);
        tabWidget->setCurrentIndex(1);
        comboBoxDisplay_4->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionopen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        actionclose->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        Reports->setText(QApplication::translate("MainWindow", "Reports", Q_NULLPTR));
        actionDistorition->setText(QApplication::translate("MainWindow", "Distorition", Q_NULLPTR));
        actionChiefRayAngle->setText(QApplication::translate("MainWindow", "ChiefRayAngle", Q_NULLPTR));
        actionRelativeIllumination->setText(QApplication::translate("MainWindow", "RelativeIllumination", Q_NULLPTR));
        actionDistoritionMultiple->setText(QApplication::translate("MainWindow", "DistoritionMultiple", Q_NULLPTR));
        actionChiefRayAngleMultiple->setText(QApplication::translate("MainWindow", "ChiefRayAngleMultiple", Q_NULLPTR));
        actionRelativeIlluminationMultiple->setText(QApplication::translate("MainWindow", "RelativeIlluminationMultiple", Q_NULLPTR));
        actionFFTPSFMultiple->setText(QApplication::translate("MainWindow", "FFTPSFMultiple", Q_NULLPTR));
        actionHuygensPSFMultiple->setText(QApplication::translate("MainWindow", "HuygensPSFMultiple", Q_NULLPTR));
        actionFFTPSF->setText(QApplication::translate("MainWindow", "FFTPSF", Q_NULLPTR));
        actionHuygensPSF->setText(QApplication::translate("MainWindow", "HuygensPSF", Q_NULLPTR));
        YourSetting->setText(QApplication::translate("MainWindow", " YourSetting:", Q_NULLPTR));
        labelFieldHTNumber->setText(QApplication::translate("MainWindow", "FieldHTNum:", Q_NULLPTR));
        labelFieldHTMin->setText(QApplication::translate("MainWindow", "FieldHTMin:", Q_NULLPTR));
        labelFieldHTMax->setText(QApplication::translate("MainWindow", "FieldHTMax:", Q_NULLPTR));
        labelallFieldtype->setText(QApplication::translate("MainWindow", "Fieldtype:", Q_NULLPTR));
        comboBoxAllFieldtype->clear();
        comboBoxAllFieldtype->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Angle", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ObjectHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ParaxialImageHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "RealImageHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "TheodoliteAngle", Q_NULLPTR)
        );
        comboBoxAllFieldtype->setCurrentText(QApplication::translate("MainWindow", "Angle", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(pageFields), QApplication::translate("MainWindow", "Fields", Q_NULLPTR));
        labelWaveNumber->setText(QApplication::translate("MainWindow", "WaveNumber:", Q_NULLPTR));
        labelWaveMin->setText(QApplication::translate("MainWindow", "WaveMin(nm):", Q_NULLPTR));
        lineEditWavelengthMin->setText(QString());
        labelWaveMax->setText(QApplication::translate("MainWindow", "WaveMax(nm):", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(pageWavelengths), QApplication::translate("MainWindow", "Wavelengths", Q_NULLPTR));
        comboBoxRayAiming->clear();
        comboBoxRayAiming->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Off", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Paraxial", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Real", Q_NULLPTR)
        );
        toolBox->setItemText(toolBox->indexOf(pageRayAming), QApplication::translate("MainWindow", "RayAming", Q_NULLPTR));
        labelAllSampling->setText(QApplication::translate("MainWindow", "Sampling", Q_NULLPTR));
        comboBoxAllSampling->clear();
        comboBoxAllSampling->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "32x32", Q_NULLPTR)
         << QApplication::translate("MainWindow", "64x64", Q_NULLPTR)
         << QApplication::translate("MainWindow", "128x128", Q_NULLPTR)
         << QApplication::translate("MainWindow", "256x256", Q_NULLPTR)
         << QApplication::translate("MainWindow", "512x512", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1024x1024", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2048x2048", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4096x4096", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8192x8192", Q_NULLPTR)
         << QApplication::translate("MainWindow", "16384x16384", Q_NULLPTR)
        );
        labelAllDisplay->setText(QApplication::translate("MainWindow", "Display", Q_NULLPTR));
        comboBoxAllDisplay->clear();
        comboBoxAllDisplay->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "32x32", Q_NULLPTR)
         << QApplication::translate("MainWindow", "64x64", Q_NULLPTR)
         << QApplication::translate("MainWindow", "128x128", Q_NULLPTR)
         << QApplication::translate("MainWindow", "256x256", Q_NULLPTR)
         << QApplication::translate("MainWindow", "512x512", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1024x1024", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2048x2048", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4096x4096", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8192x8192", Q_NULLPTR)
         << QApplication::translate("MainWindow", "16384x16384", Q_NULLPTR)
        );
        labelAllImageDelta->setText(QApplication::translate("MainWindow", "ImgDelta(um)", Q_NULLPTR));
        lineEditAllImageDelta->setText(QString());
        pushButtonRunning->setText(QApplication::translate("MainWindow", "   Running    ", Q_NULLPTR));
        pushButtonCanceling->setText(QApplication::translate("MainWindow", "  Canceling  ", Q_NULLPTR));
        radioButton_FFTPSFMultiple->setText(QApplication::translate("MainWindow", "FFTPSF", Q_NULLPTR));
        radioButton_HuygensPSFMultiple->setText(QApplication::translate("MainWindow", "HuygensPSF   ", Q_NULLPTR));
        checkBoxDistortionMultiple->setText(QApplication::translate("MainWindow", "DistortionMultiple", Q_NULLPTR));
        checkBoxChiefRayAngleMultiple->setText(QApplication::translate("MainWindow", "ChiefRayAngleMultiple", Q_NULLPTR));
        checkBoxRelativeIlluminationMultiple->setText(QApplication::translate("MainWindow", "RelativeIlluminationMultiple", Q_NULLPTR));
        checkBoxFFTPSFMultiple->setText(QApplication::translate("MainWindow", "FFTPSFMultiple", Q_NULLPTR));
        checkBoxHuygensPSFMultiple->setText(QApplication::translate("MainWindow", "HuygensPSFMultiple", Q_NULLPTR));
        lineEdit_outputpath->setText(QApplication::translate("MainWindow", "./output/", Q_NULLPTR));
        pushButton_outputpath->setText(QApplication::translate("MainWindow", "ChoosPath", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(pageTaskRunning), QApplication::translate("MainWindow", "TaskRunning", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_0), QApplication::translate("MainWindow", "Report", Q_NULLPTR));
        groupBox1DMRelatedSetting->setTitle(QApplication::translate("MainWindow", "DistortionMultiple Related Setting", Q_NULLPTR));
        labelWhichwave->setText(QApplication::translate("MainWindow", "Whichwave(prime)", Q_NULLPTR));
        lineEditWhichwave->setText(QString());
        labelFieldtype->setText(QApplication::translate("MainWindow", "Fieldtype", Q_NULLPTR));
        labelDistortiontype->setText(QApplication::translate("MainWindow", "Distortiontype", Q_NULLPTR));
        labelScantype->setText(QApplication::translate("MainWindow", "Scantype", Q_NULLPTR));
        comboBoxFieldtype->clear();
        comboBoxFieldtype->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Angle", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ObjectHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ParaxialImageHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "RealImageHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "TheodoliteAngle", Q_NULLPTR)
        );
        comboBoxScantype->clear();
        comboBoxScantype->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Plus_Y", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Plus_X", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Minus_Y", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Minus_X", Q_NULLPTR)
        );
        comboBoxDistortiontype->clear();
        comboBoxDistortiontype->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "F_TanTheta", Q_NULLPTR)
         << QApplication::translate("MainWindow", "F_Theta", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Cal_F_Theta", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Cal_F_TanTheta", Q_NULLPTR)
         << QApplication::translate("MainWindow", "SMIA_TV", Q_NULLPTR)
        );
        groupBox2CRARelatedSetting->setTitle(QApplication::translate("MainWindow", "CRAMultiple Related Setting", Q_NULLPTR));
        labelWhichwave_2->setText(QApplication::translate("MainWindow", "Whichwave(prime)", Q_NULLPTR));
        lineEditWhichwave_2->setText(QString());
        labelDirection_2->setText(QApplication::translate("MainWindow", "Direction", Q_NULLPTR));
        comboDirection_2->clear();
        comboDirection_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "y", Q_NULLPTR)
         << QApplication::translate("MainWindow", "x", Q_NULLPTR)
        );
        groupBox3RIRelatedSetting->setTitle(QApplication::translate("MainWindow", "RIMultiple Related Setting", Q_NULLPTR));
        labelWhichwave_3->setText(QApplication::translate("MainWindow", "Whichwave(prime)", Q_NULLPTR));
        lineEditWhichwave_3->setText(QString());
        comboDirection_3->clear();
        comboDirection_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "y", Q_NULLPTR)
         << QApplication::translate("MainWindow", "x", Q_NULLPTR)
        );
        labelDirection_3->setText(QApplication::translate("MainWindow", "Direction", Q_NULLPTR));
        groupBox4FFTPSFRelatedSetting->setTitle(QApplication::translate("MainWindow", "FFTPSFMultiple Related Setting", Q_NULLPTR));
        labelWhichwave_4->setText(QApplication::translate("MainWindow", "Whichwave(prime)", Q_NULLPTR));
        lineEditWhichwave_4->setText(QString());
        labelFieldtype_4->setText(QApplication::translate("MainWindow", "Fieldtype", Q_NULLPTR));
        labelSampling_4->setText(QApplication::translate("MainWindow", "Sampling", Q_NULLPTR));
        labelScantype_4->setText(QApplication::translate("MainWindow", "Scantype", Q_NULLPTR));
        comboBoxFieldtype_4->clear();
        comboBoxFieldtype_4->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Angle", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ObjectHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ParaxialImageHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "RealImageHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "TheodoliteAngle", Q_NULLPTR)
        );
        comboBoxScantype_4->clear();
        comboBoxScantype_4->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Plus_Y", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Plus_X", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Minus_Y", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Minus_X", Q_NULLPTR)
        );
        comboBoxSampling_4->clear();
        comboBoxSampling_4->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "32x32", Q_NULLPTR)
         << QApplication::translate("MainWindow", "64x64", Q_NULLPTR)
         << QApplication::translate("MainWindow", "128x128", Q_NULLPTR)
         << QApplication::translate("MainWindow", "256x256", Q_NULLPTR)
         << QApplication::translate("MainWindow", "512x512", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1024x1024", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2048x2048", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4096x4096", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8192x8192", Q_NULLPTR)
         << QApplication::translate("MainWindow", "16384x16384", Q_NULLPTR)
        );
        labelDisplay_4->setText(QApplication::translate("MainWindow", "Display", Q_NULLPTR));
        lineEditImageDelta_4->setText(QString());
        labelImageDelta_4->setText(QApplication::translate("MainWindow", "Image Delta(um)", Q_NULLPTR));
        comboBoxType_4->clear();
        comboBoxType_4->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Linear", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Log", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Phase", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Real", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Imaginary", Q_NULLPTR)
        );
        labelType_4->setText(QApplication::translate("MainWindow", "Type", Q_NULLPTR));
        checkBoxNormalize_4->setText(QApplication::translate("MainWindow", "Normalize", Q_NULLPTR));
        comboBoxDisplay_4->clear();
        comboBoxDisplay_4->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "32x32", Q_NULLPTR)
         << QApplication::translate("MainWindow", "64x64", Q_NULLPTR)
         << QApplication::translate("MainWindow", "128x128", Q_NULLPTR)
         << QApplication::translate("MainWindow", "256x256", Q_NULLPTR)
         << QApplication::translate("MainWindow", "512x512", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1024x1024", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2048x2048", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4096x4096", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8192x8192", Q_NULLPTR)
         << QApplication::translate("MainWindow", "16384x16384", Q_NULLPTR)
        );
        groupBox5HuygensPSFRelatedSetting->setTitle(QApplication::translate("MainWindow", "HuygensPSFMultiple Related Setting", Q_NULLPTR));
        labelWhichwave_5->setText(QApplication::translate("MainWindow", "Whichwave(prime)", Q_NULLPTR));
        lineEditWhichwave_5->setText(QString());
        labelFieldtype_5->setText(QApplication::translate("MainWindow", "Fieldtype", Q_NULLPTR));
        labelSampling_5->setText(QApplication::translate("MainWindow", "Sampling", Q_NULLPTR));
        labelScantype_5->setText(QApplication::translate("MainWindow", "Scantype", Q_NULLPTR));
        comboBoxFieldtype_5->clear();
        comboBoxFieldtype_5->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Angle", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ObjectHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ParaxialImageHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "RealImageHeight", Q_NULLPTR)
         << QApplication::translate("MainWindow", "TheodoliteAngle", Q_NULLPTR)
        );
        comboBoxScantype_5->clear();
        comboBoxScantype_5->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Plus_Y", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Plus_X", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Minus_Y", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Minus_X", Q_NULLPTR)
        );
        comboBoxSampling_5->clear();
        comboBoxSampling_5->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "32x32", Q_NULLPTR)
         << QApplication::translate("MainWindow", "64x64", Q_NULLPTR)
         << QApplication::translate("MainWindow", "128x128", Q_NULLPTR)
         << QApplication::translate("MainWindow", "256x256", Q_NULLPTR)
         << QApplication::translate("MainWindow", "512x512", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1024x1024", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2048x2048", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4096x4096", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8192x8192", Q_NULLPTR)
         << QApplication::translate("MainWindow", "16384x16384", Q_NULLPTR)
        );
        labelDisplay_5->setText(QApplication::translate("MainWindow", "Display", Q_NULLPTR));
        lineEditImageDelta_5->setText(QString());
        labelImageDelta_5->setText(QApplication::translate("MainWindow", "Image Delta(um)", Q_NULLPTR));
        comboBoxType_5->clear();
        comboBoxType_5->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Linear", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Log_Minus_1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Log_Minus_2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Log_Minus_3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Log_Minus_4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Log_Minus_5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Real", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Imaginary", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Phase", Q_NULLPTR)
        );
        labelType_5->setText(QApplication::translate("MainWindow", "Type", Q_NULLPTR));
        checkBoxNormalize_5->setText(QApplication::translate("MainWindow", "Normalize", Q_NULLPTR));
        comboBoxDisplay_5->clear();
        comboBoxDisplay_5->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "32x32", Q_NULLPTR)
         << QApplication::translate("MainWindow", "64x64", Q_NULLPTR)
         << QApplication::translate("MainWindow", "128x128", Q_NULLPTR)
         << QApplication::translate("MainWindow", "256x256", Q_NULLPTR)
         << QApplication::translate("MainWindow", "512x512", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1024x1024", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2048x2048", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4096x4096", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8192x8192", Q_NULLPTR)
         << QApplication::translate("MainWindow", "16384x16384", Q_NULLPTR)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Setting", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuAnalyse->setTitle(QApplication::translate("MainWindow", "Analyse", Q_NULLPTR));
        menuPFS->setTitle(QApplication::translate("MainWindow", "PSF", Q_NULLPTR));
        menuDistorition->setTitle(QApplication::translate("MainWindow", "Distorition", Q_NULLPTR));
        menuChiefRayAngle->setTitle(QApplication::translate("MainWindow", "ChiefRayAngle", Q_NULLPTR));
        menuRelativeIllumination->setTitle(QApplication::translate("MainWindow", "RelativeIllumination", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZEMAXQT_H
