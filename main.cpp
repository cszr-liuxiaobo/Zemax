#include "stdafx.h"
#include "Background.h"
#include "zemaxqt.h"
#include <QtWidgets/QApplication>
#include "windows.h"
#pragma execution_character_set("unicode")

int main(int argc, char* argv[])
{
    ShowWindow(GetForegroundWindow(), 0);//获取最前端窗口的句柄，然后通过ShowWindow隐藏 、
    backStage Back1;

    cout << "argc::" << argc << endl;
    cout << "argv::" << argv[0] <<"----"<< typeid(argv[0]).name() << endl;

    string argv0= argv[0];
    string bk = "background";
    //在这里做一个判断，如果第一个argv[0]="background",的话就直接调用纯后台处理任务，返回进程（后续杀死进程用），不启动qt。否则就打开QT进行界面操作。
    if (argv0 == bk) {
        //设定一个argv的接收规则，分别按顺序获取并放入对应的模块中
        int pid = GetCurrentProcessId();
        cout << "back processing::" <<pid<< endl;
        Back1.backgroundProcessing(argc, argv);
        return pid;
    }
    else {
        QApplication a(argc, argv);
        QFont f("黑体", 15);
        a.setFont(f);
        zemaxqt w;
        w.setWindowTitle("ZLens");
        w.show();
        return a.exec();
    }
}
