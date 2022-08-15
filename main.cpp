#include "stdafx.h"
#include "Background.h"
#include "zemaxqt.h"
#include <QtWidgets/QApplication>
#include "windows.h"
#pragma execution_character_set("unicode")

int main(int argc, char* argv[])
{
    backStage Back1;

    cout << "argc::" << argc << endl;
    cout << "argv::" << argv[0] <<"----"<< typeid(argv[0]).name() << endl;

    string argv0= argv[0];
    string bk = "background";
    //��������һ���жϣ������һ��argv[0]="background",�Ļ���ֱ�ӵ��ô���̨�������񣬷��ؽ��̣�����ɱ�������ã���������qt������ʹ�QT���н��������
    if (argv0 == bk) {
        //�趨һ��argv�Ľ��չ��򣬷ֱ�˳���ȡ�������Ӧ��ģ����
        int pid = GetCurrentProcessId();
        cout << "back processing::" <<pid<< endl;
        Back1.backgroundProcessing(argc, argv);
        return pid;
    }
    else {
        QApplication a(argc, argv);
        QFont f("����", 15);
        a.setFont(f);
        zemaxqt w;
        w.setWindowTitle("ZLens");
        w.show();
        return a.exec();
    }
}
