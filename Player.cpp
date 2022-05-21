#include "Player.h"
#include "ui_Player.h"

#include "ffmpeg.h"
#include "worker.h"
#include "audio.h"
#include "medialib.h"
#include <QDesktopWidget>
#include <QMutex>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QIODevice>
#include <QTime>
#include <QImage>
#include <QObject>
#include <QIODevice>
#include <QAudioFormat>
#include<QAudioOutput>
#include <QMutex>
#include <QDebug>
#include <QTime>
#include <QDateTime>
#include <QOpenGLWidget>

AudioPlay::AudioPlay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AudioPlay)
{
    ui->setupUi(this);

//    player      = new QMediaPlayer;
//    playerList  = new QMediaPlaylist;
    //videoPlayWidget = new videowidget;
    // 在当前路径创建一个文件（文件名PlayList.ini）把音视频输出到里面，方便下一次播放

//    playerIndex = 0;
//    playerPrevious = 0;
//    playerMode = 0;

//    player->setVolume(50);             // 设置初始音量
//    playerList->setPlaybackMode(QMediaPlaylist::Loop);                       // 循环播放模式


    if(connect(worker::Get(), SIGNAL(sig_Send(QImage,double)), this, SLOT(sig_Recv(QImage,double)))){
        qDebug()<<"bind success";
    }else{
        qDebug()<<"failed";
    }

    if(connect(worker::Get(), SIGNAL(sig_End()), this, SLOT(sig_rEnd()))){
        qDebug()<<"bind success";
    }else{
        qDebug()<<"failed2";
    }

    if(connect(worker::Get(), SIGNAL(audio_send(double)), this, SLOT(audio_recv(double)))){
        qDebug()<<"bind success";
    }else{
        qDebug()<<"failed3";
    }

    ui->Slider_Volume->setValue(50);
    ui->label_Volume->setText("50%");
    // 允许文件拖拽到窗口部分
    this->setAcceptDrops(true);
    mLocation = this->geometry();
    mIsMax = false;
    mDrag = false;
    //


    // 手动添加窗口顶部处理部分
    this->installEventFilter(this); // 事件过滤器就是接收所有被发送到这个对象的事件的对象

    ui->pushButton_WindowMin->setIcon(QIcon(":/image/jianhao.png"));
    ui->pushButton_WindowMin->setIconSize(QSize(16,16));

    ui->pushButton_WindowMax->setIcon(QIcon(":/image/fangkuang.png"));
    ui->pushButton_WindowMin->setIconSize(QSize(16,16));

    ui->pushButton_WindowExit->setIcon(QIcon(":/image/guanbi.png"));
    ui->pushButton_WindowMin->setIconSize(QSize(16,16));



    ui->pushButton_WindowMin->setFlat(true);
    ui->pushButton_WindowMin->setStyleSheet("QPushButton{border:none;background:transparent;}");

    ui->pushButton_WindowMax->setFlat(true);
    ui->pushButton_WindowMax->setStyleSheet("QPushButton{border:none;background:transparent;}");

    ui->pushButton_WindowExit->setFlat(true);
    ui->pushButton_WindowExit->setStyleSheet("QPushButton{border:none;background:transparent;}");

    ui->tableWidget->setShowGrid(false);//隐藏表格线
       setStyleSheet("QMainWindow{color:#E8E8E8;background:#43CD80;}");
//       //另外在设计器内查看widgetTitle样式，内有标题栏各个子控件的样式设置



//    // 设置窗口名称，图标
    this->setWindowTitle(QTextCodec::codecForName("GBK")->toUnicode("MediaPlayer"));
    this->setWindowIcon(QIcon(":/image/icon.png"));

       QPixmap *pixmap = new QPixmap(":/image/icon.png");
       pixmap->scaled(ui->logo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
       ui->logo->setScaledContents(true);
       ui->logo->setPixmap(*pixmap);
       ui->label_Title->setText(QTextCodec::codecForName("GBK")->toUnicode("Player"));
       QFont ft( "Microsoft YaHei", 12, 75);
       ui->label_Title->setFont(ft);

    // 设置背景图片为bj.jpg
    this->setObjectName("mainWindow");
    this->setStyleSheet("#mainWindow{border-image:url(:/image/bj.png);}");

    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
//    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明

//    this->setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    // 设置按键图标
    ui->PushButton_PlayStop->setIcon(QIcon(":/image/bofang.png"));
    ui->PushButton_PlayStop->setIconSize(QSize(55,55));

    ui->PushButton_PlayMode->setIcon(QIcon(":/image/yinlebofangye-xunhuanbofang.png"));
    ui->PushButton_PlayMode->setIconSize(QSize(48,48));

    ui->PushButton_Previous->setIcon(QIcon(":/image/shangyishou.png"));
    ui->PushButton_Previous->setIconSize(QSize(48,48));

    ui->PushButton_Next->setIcon(QIcon(":/image/xiayishou.png"));
    ui->PushButton_Next->setIconSize(QSize(48,48));

    ui->PushButton_OpenFile->setIcon(QIcon(":/image/tianjiagequ.png"));
    ui->PushButton_OpenFile->setIconSize(QSize(48,48));

    ui->PushButton_DeleteMusic->setIcon(QIcon(":/image/shanchu.png"));
    ui->PushButton_DeleteMusic->setIconSize(QSize(48,48));


    QPixmap *pixmap1 = new QPixmap(":/image/jurassic.png");
    pixmap->scaled(QSize(16,16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_Volume_2->setScaledContents(true);
    ui->label_Volume_2->setPixmap(*pixmap1);

    // 设置图标为透明

    ui->PushButton_PlayStop->setFlat(true);
    ui->PushButton_PlayStop->setStyleSheet("QPushButton{border:none;background:transparent;}");

    ui->PushButton_PlayMode->setFlat(true);
    ui->PushButton_PlayMode->setStyleSheet("QPushButton{border:none;background:transparent;}");

    ui->PushButton_Previous->setFlat(true);
    ui->PushButton_Previous->setStyleSheet("QPushButton{border:none;background:transparent;}");

    ui->PushButton_Next->setFlat(true);
    ui->PushButton_Next->setStyleSheet("QPushButton{border:none;background:transparent;}");

    ui->PushButton_OpenFile->setFlat(true);
    ui->PushButton_OpenFile->setStyleSheet("QPushButton{border:none;background:transparent;}");

    ui->PushButton_DeleteMusic->setFlat(true);
    ui->PushButton_DeleteMusic->setStyleSheet("QPushButton{border:none;background:transparent;}");

    ui->label_Volume->setStyleSheet("QLabel{border:none;background:transparent;}");

    ui->label_MusicTime->setStyleSheet("QLabel{border:none;background:transparent;}");

    ui->label_PlayTime->setStyleSheet("QLabel{border:none;background:transparent;}");

    ui->Slider_Volume->setStyleSheet("QSlider{border:none;background:transparent;}");

    ui->Slider_ProgressBar->setStyleSheet("QSlider{border:none;background:transparent;}");

    ui->label_Volume_2->setStyleSheet("QLabel{border:none;background:transparent;}");

    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->setStyleSheet("QTableView::item:selected{color:black;background:black;}");
    ui->tableWidget->setStyleSheet("QTableWidget{border:none;background:transparent;}");


    //设置进度条的步长
    ui->Slider_ProgressBar->setMinimum(0);  // 最小值
    ui->Slider_ProgressBar->setSingleStep(1);  // 步长
    // 读取配置文件的内容：歌曲名 把前一次写入的歌曲读出来
    playList=mediaLib::Get()->getAll(fileList);
    foreach(QString s, playList){
        int rownum=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rownum);
        ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem(s));
    }

    playMode=1;   //初始为列表循环播放

    ui->lab22->setGeometry(1,1,812,595);
    ffmpeg::get()->width=ui->lab22->width();
    ffmpeg::get()->height=ui->lab22->height();
    worker::Get()->start();
//    for(int i=0; ; ++i) //  将所有的播放列表显示在列表控件中
//    {
//        if(configIniRead->value("/song/"+QString::number(i),100).toInt()!=100)
//        {
//            QString path = configIniRead->value("/song/"+QString::number(i)).toString();


//            playerList->addMedia(QUrl::fromLocalFile(path));

//            QFileInfo fileInfo;
//            fileInfo = QFileInfo(path);
//            QString fileName = fileInfo.completeBaseName(); //  文件名不带后缀
//            QString fileSuffix = fileInfo.suffix(); //  文件后缀

//            int rownum=ui->tableWidget->rowCount();
//            ui->tableWidget->insertRow(rownum);
//            ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem(fileName + "." + fileSuffix));
//        }
//        else
//        {
//            break;
//        }
//    }
//    player->setPlaylist(playerList); // 把播放列表添加到播放器
//    playerList->setCurrentIndex(0);
}

AudioPlay::~AudioPlay()
{
    delete ui;
}

void delay(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void AudioPlay::sig_Recv(QImage img,double pts){
    this->ui->lab22->setPixmap(QPixmap::fromImage(img)); // 在label上播放视频图片
    ui->lab22->setScaledContents(true);
//    int tatal=ffmpeg::get()->m_totalMs;   //视频的总长度
//    int pos=(int)pts;
//    ui->Slider_ProgressBar->setMaximum(tatal+1);  // 最大值
//    ui->Slider_ProgressBar->setValue(pos);

//    QString nowTime=QDateTime::fromTime_t(pos).toString("mm:ss");
//    QString totTime=QDateTime::fromTime_t(tatal).toString("mm:ss");
//    ui->label_PlayTime->setText(nowTime);
//    ui->label_MusicTime->setText(totTime);
}

void AudioPlay::audio_recv(double pts){
    if(mDrag==true)return ;
    int tatal=ffmpeg::get()->m_totalMs;   //视频的总长度
    int pos=(int)pts;
    ui->Slider_ProgressBar->setMaximum(tatal+1);  // 最大值
    ui->Slider_ProgressBar->setValue(pos);
    QString nowTime=QDateTime::fromTime_t(pos).toString("mm:ss");
    QString totTime=QDateTime::fromTime_t(tatal).toString("mm:ss");
    ui->label_PlayTime->setText(nowTime);
    ui->label_MusicTime->setText(totTime);
}
void AudioPlay::sig_rEnd(){
    QString tname=worker::Get()->filename;
    foreach(QString nstr,fileList){
        if(nstr==tname){      //在播放列表中
            if(playMode==1){
                QString strn=tname.split('/').back();
                for(int i=0;i<playList.size();i++){
                    if(playList[i]==strn){
                        i=(i+1)%playList.size();
                        worker::Get()->filename=fileList[i];
                        worker::Get()->isChanged=true;
                        worker::Get()->isStop=false;
                        worker::Get()->isPause=false;
                        worker::Get()->audioPts=0;
                        //选中tableWidget的对应行
                        ui->tableWidget->selectRow(i);
                        return ;
                    }
                }
            }else if(playMode==2){   //单曲循环播放
                worker::Get()->isChanged=true;
                worker::Get()->isStop=false;
                worker::Get()->isPause=false;
                worker::Get()->audioPts=0;
                return ;
            }else{
                int npos=rand()%playList.size();
                worker::Get()->filename=fileList[npos];
                worker::Get()->isChanged=true;
                worker::Get()->isStop=false;
                worker::Get()->audioPts=0;
                worker::Get()->isPause=false;
                //选中tableWidget的对应行
                ui->tableWidget->selectRow(npos);
                return ;
            }
        }
    }
    //不再列表则暂停播放
    ui->PushButton_PlayStop->setIcon(QIcon(":/image/bofang.png"));
    ui->PushButton_PlayStop->setIconSize(QSize(55,55));
}
// 打开文件
void AudioPlay::on_PushButton_OpenFile_clicked()
{
    QString name = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择视频文件"),"",tr("mp4(*.mp4);;mp3(*mp3);;PNG Files(*.png);;PGM Files(*.pgm)"));
    QStringList list=name.split("/");
    mediaLib::Get()->addToLib(list.back(),name);
    foreach(QString s,playList){
        if(s==list.back()){
            QMessageBox::about(this,"视频已经在媒体库中",NULL);
            return ;
        }
    }

    playList.append(list.back());
    fileList.append(name);
    int rownum=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rownum);
    ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem(playList.back()));
}

void AudioPlay::findFormat(QString &path, QStringList format, QList<QString>& receiveFilePath)
{
    // 判断路径是否存在
    QDir dir(path);
    if(!dir.exists())   return;


    // 定义迭代器并设置过滤器
    QDirIterator dirIterator(path, format, QDir::Files | QDir::NoSymLinks,QDirIterator::Subdirectories);
    while(dirIterator.hasNext())
    {
        dirIterator.next();
        receiveFilePath.append(dirIterator.fileInfo().absoluteFilePath());
    }
}

// 播放音乐
void AudioPlay::playMusic(int index,int Method)   //index是播放列表中的行号
{
//    QString name;
//    if(Method==1){
//        name = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择视频文件"),"",tr("mp4(*.mp4);;PNG Files(*.png);;PGM Files(*.pgm)"));
//    }else if(Method==2){
//        QString key=ui->tableWidget->item(index,0)->text();
//        QSettings* set=new QSettings("D:/PlayList.ini", QSettings::IniFormat);
//        name=set->value("/song/"+key).toString();
//    }
//    qDebug()<<name;
//    if(name==""||name.size()==0)return ;
//    char* str=name.toLatin1().data();

//    ffmpeg::get()->readFile(str);
//    ffmpeg::get()->m_isPlay=true;
//    Playing=true;
//    worker::Get()->isExit=false;
//    qDebug()<<"file open successfully";
//    worker::Get()->start();
//    char out[10000] = {0};
//    bool mark=false;
//    while(Playing){
//        qDebug()<<"2";
//        if (!ffmpeg::get()->m_isPlay)//如果为暂停状态，不处理
//        {
//            //sleep(10);
//            delay(50);
//            qDebug()<<"3";
//            continue;
//        }
//        vedio_frame* vf=new vedio_frame();
//        audio_frame* af=new audio_frame();
//        af->pts=2147483647;
//        vf->pts=2147483647;

//        worker::Get()->get_Mutex().lock();
//        if(worker::Get()->aList.size()>0){
//            af=&worker::Get()->aList.front();
//            qDebug()<<"4";
//        }
//        if(worker::Get()->vList.size()>0){
//            qDebug()<<"5";
//            vf=&worker::Get()->vList.front();
//        }
//        worker::Get()->get_Mutex().unlock();


//        if(af->pts<=vf->pts){  //处理音频
//            if(af->pts==2147483647){
//                qDebug()<<"6";
//                qDebug()<<"MainWindow AAA size=="<<worker::Get()->aList.size();
//                delay(10);
//                continue ;
//            }
//            qDebug()<<"7";
//            if(mark==false){
//                mark=true;
//                XAudioPlay::Get()->Start();
//            }
//            int len = ffmpeg::get()->toPCM(out,&af->aFrame);//重采样音频
//            //qDebug()<<"AUDIO STREAM >>>>>>>"<<out;
//            XAudioPlay::Get()->Write(out, len);//写入音频
//            worker::Get()->aList.pop_front();
//        }else{             //处理视频
//            //AVFrame* vf=&vList.front().vFrame;
//            qDebug()<<"8";
//            qDebug()<<"MainWindow VVV size=="<<worker::Get()->vList.size();
//            QImage img=ffmpeg::get()->toRGB(&vf->vFrame);

//            this->ui->lab22->setPixmap(QPixmap::fromImage(img)); // 在label上播放视频图片

//            worker::Get()->get_Mutex().lock();
//            worker::Get()->vList.pop_front();
//            worker::Get()->get_Mutex().unlock();
//        }
//    }
}


// 双击触发槽函数
void AudioPlay::on_tableWidget_cellDoubleClicked(int row, int column)
{
    qDebug()<<"row:"<<row << "col:"<<column;
//    ui->tableWidget->clearFocus();
//    playMusic(row);
    //playMusic(row,2);
    QString filename=ui->tableWidget->item(row,column)->text();
    //qDebug()<<filename;
    QString name=mediaLib::Get()->getValue(filename);
    if(name!=""&&name.size()!=0){
        worker::Get()->filename=name;
        worker::Get()->isChanged=true;
        worker::Get()->isStop=false;
        worker::Get()->isPause=false;
        worker::Get()->audioPts=0;
        ui->PushButton_PlayStop->setIcon(QIcon(":/image/zanting-xian.png"));
        ui->PushButton_PlayStop->setIconSize(QSize(48,48));
    }
}


// 播放和停止槽函数
void AudioPlay::on_PushButton_PlayStop_clicked()
{
    if(worker::Get()->isStop==true){        //现在没有在播放视频
        QString name = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择视频文件"),"",tr("mp4(*.mp4);;MP3(*.mp3);;PNG Files(*.png);;PGM Files(*.pgm)"));
        if(name!=""&&name.size()!=0){
            for(int i=0;i<fileList.size();i++){
                if(fileList[i]==name){
                    ui->tableWidget->selectRow(i);
                }
            }

            worker::Get()->filename=name;
            worker::Get()->isChanged=true;
            worker::Get()->isStop=false;
            worker::Get()->isPause=false;
            worker::Get()->audioPts=0;
            ui->PushButton_PlayStop->setIcon(QIcon(":/image/zanting-xian.png"));
            ui->PushButton_PlayStop->setIconSize(QSize(48,48));
        }
    }else {
        if(worker::Get()->isPause==true){
            worker::Get()->isPause=false;
            ui->PushButton_PlayStop->setIcon(QIcon(":/image/zanting-xian.png"));
            ui->PushButton_PlayStop->setIconSize(QSize(48,48));
        }else{
            worker::Get()->isPause=true;
            ui->PushButton_PlayStop->setIcon(QIcon(":/image/bofang.png"));
            ui->PushButton_PlayStop->setIconSize(QSize(55,55));
        }
    }
//    if(Playing==false){  //在播放
//        Playing=true;
//        ui->PushButton_PlayStop->setIcon(QIcon(":/image/zanting-xian.png"));
//        ui->PushButton_PlayStop->setIconSize(QSize(48,48));
//        playMusic(0,1);
//    }else{
//        if(ffmpeg::get()->m_isPlay==false){  //暂停中
//            ui->PushButton_PlayStop->setIcon(QIcon(":/image/bofang.png"));
//            ui->PushButton_PlayStop->setIconSize(QSize(48,48));
//            ffmpeg::get()->m_isPlay=true;
//        }else{
//            ui->PushButton_PlayStop->setIcon(QIcon(":/image/zanting-xian.png"));
//            ui->PushButton_PlayStop->setIconSize(QSize(48,48));
//            ffmpeg::get()->m_isPlay=true;
//        }
    //playMusic(0);
//    if(player->state() == QMediaPlayer::PlayingState) // 判断当前播放状态
//    {
//        player->pause();
//        ui->PushButton_PlayStop->setIcon(QIcon(":/image/bofang.png"));
//        ui->PushButton_PlayStop->setIconSize(QSize(48,48));
//    }
//    else
//    {
//        playMusic(playerList->currentIndex());
//    }
}

// 上一曲
void AudioPlay::on_PushButton_Previous_clicked()
{
    QString tname=worker::Get()->filename;
    foreach(QString nstr,fileList){
        if(nstr==tname){      //在播放列表中
            QString strn=tname.split('/').back();
            for(int i=0;i<playList.size();i++){
                if(playList[i]==strn){
                    i=i-1;
                    if(i<0){
                        i=playList.size()-1;
                    }
                    worker::Get()->filename=fileList[i];
                    worker::Get()->isChanged=true;
                    worker::Get()->isStop=false;
                    worker::Get()->isPause=false;
                    worker::Get()->audioPts=0;
                    //选中tableWidget的对应行
                    ui->tableWidget->selectRow(i);
                    ui->PushButton_PlayStop->setIcon(QIcon(":/image/zanting-xian.png"));
                    ui->PushButton_PlayStop->setIconSize(QSize(48,48));
                    return ;
                }
            }
        }
    }
    //若当前播放的视频不在列表中，则选择列表第一个视频
    int n=fileList.size()-1;
    worker::Get()->filename=fileList[n];
    worker::Get()->isChanged=true;
    worker::Get()->isStop=false;
    worker::Get()->isPause=false;
    worker::Get()->audioPts=0;
    //选中tableWidget的对应行
    ui->tableWidget->selectRow(n);
    ui->PushButton_PlayStop->setIcon(QIcon(":/image/zanting-xian.png"));
    ui->PushButton_PlayStop->setIconSize(QSize(48,48));
}

// 下一曲
void AudioPlay::on_PushButton_Next_clicked()
{
    QString tname=worker::Get()->filename;

    foreach(QString nstr,fileList){
        if(nstr==tname){      //在播放列表中
            QString strn=tname.split('/').back();
            for(int i=0;i<playList.size();i++){
                if(playList[i]==strn){
                    i=(i+1)%playList.size();
                    worker::Get()->filename=fileList[i];
                    worker::Get()->isChanged=true;
                    worker::Get()->isStop=false;
                    worker::Get()->isPause=false;
                    worker::Get()->audioPts=0;
                    //选中tableWidget的对应行
                    ui->tableWidget->selectRow(i);
                    ui->PushButton_PlayStop->setIcon(QIcon(":/image/zanting-xian.png"));
                    ui->PushButton_PlayStop->setIconSize(QSize(48,48));
                    return ;
                }
            }
        }
    }
    //若当前播放的视频不在列表中，则选择列表最后一个视频
    worker::Get()->filename=fileList[0];
    worker::Get()->isChanged=true;
    worker::Get()->isStop=false;
    worker::Get()->isPause=false;
    worker::Get()->audioPts=0;
    //选中tableWidget的对应行
    ui->tableWidget->selectRow(0);
    ui->PushButton_PlayStop->setIcon(QIcon(":/image/zanting-xian.png"));
    ui->PushButton_PlayStop->setIconSize(QSize(48,48));
}

// 设置音量
void AudioPlay::on_Slider_Volume_valueChanged(int value)
{
    ui->label_Volume->setText(QString::number(value)+"%");
    XAudioPlay::Get()->setVolume(value);
}


// 获取歌曲时长,歌曲改变时才会执行这个槽函数
void AudioPlay::do_getduration_slots(qint64 playtime)
{
//    qDebug() << __FUNCTION__;

//    playtime = player->duration();  // 获取时间
//    GetTime(playtime);

//    ui->Slider_ProgressBar->setRange(0,playtime); // 根据播放时长来设置滑块的范围
//    ui->Slider_ProgressBar->setEnabled(playtime > 0);
//    ui->Slider_ProgressBar->setPageStep(playtime / 10); // 以及每一步的步数

//    // 前一首设置为黑色
//    QTableWidgetItem *FileName1 = new QTableWidgetItem(ui->tableWidget->item(playerPrevious,0)->text());
//    FileName1->setTextColor(QColor(Qt::black));
//    ui->tableWidget->setItem(playerPrevious,0,FileName1);

//    // 当前设置为蓝绿色
//    QTableWidgetItem *FileName = new QTableWidgetItem(ui->tableWidget->item(playerList->currentIndex(),0)->text());
//    FileName->setTextColor(QColor(Qt::cyan));
//    ui->tableWidget->setItem(playerList->currentIndex(),0,FileName);

//    playerPrevious = playerList->currentIndex();
}

// 计算时间
void AudioPlay::GetTime(qint64 playtime)
{
    int h,m,s;
    playtime /= 1000;  //获得的时间是以毫秒为单位的
    h = playtime/3600;
    m = (playtime-h*3600)/60;
    s = playtime-h*3600-m*60;

    ui->label_MusicTime->setText(QString("%1:%2:%3").arg(h,2,10,QLatin1Char('0')).arg(m,2,10,QLatin1Char('0')).arg(s,2,10,QLatin1Char('0')));  // 把int型转化为string类型后再设置为label的text
/*    ui->label_MusicTime->setStyleSheet("color:white");    */               // 设置字体颜色为白色

    }


// 接收歌曲位置改变，改变进度条
void AudioPlay::do_updatePosition_slots(qint64 position)
{
    int h,m,s;

    ui->Slider_ProgressBar->setValue(position);//设置滑块位置

    position /= 1000;  //获得的时间是以毫秒为单位的
    h = position/3600;
    m = (position-h*3600)/60;
    s = position-h*3600-m*60;
    //     arg(整数类型,补位数,进制,补位字符);
    ui->label_PlayTime->setText(QString("%1:%2:%3").arg(h,2,10,QLatin1Char('0')).arg(m,2,10,QLatin1Char('0')).arg(s,2,10,QLatin1Char('0')));  // 把int型转化为string类型后再设置为label的text
}

// 拖动进度松手槽函数
void AudioPlay::on_Slider_ProgressBar_sliderReleased()
{

    double pos = 0;
    mDrag=false;
    //松开时此时滑动条的位置与滑动条的总长度
    worker::Get()->isPause=true;
    worker::Get()->slidown=true;
    pos = (float)ui->Slider_ProgressBar->value() / (double)(ui->Slider_ProgressBar->maximum() + 1);

    ffmpeg::get()->Seek(pos);
    worker::Get()->isPause=false;
    ui->PushButton_PlayStop->setIcon(QIcon(":/image/zanting-xian.png"));
    ui->PushButton_PlayStop->setIconSize(QSize(48,48));
}

// 设置播放模式槽函数
void AudioPlay::on_PushButton_PlayMode_clicked()
{
    ++playMode;
    if(playMode==4)playMode=1;
    switch (playMode) {
        case 1: ui->PushButton_PlayMode->setIcon(QIcon(":/image/yinlebofangye-xunhuanbofang.png"));
                ui->PushButton_PlayMode->setIconSize(QSize(48,48));
        break ;
        case 2: ui->PushButton_PlayMode->setIcon(QIcon(":/image/danquxunhuan.png"));
                ui->PushButton_PlayMode->setIconSize(QSize(48,48));
        break;
        case 3: ui->PushButton_PlayMode->setIcon(QIcon(":/image/suijibofang.png"));
                ui->PushButton_PlayMode->setIconSize(QSize(48,48));
    }

//   qDebug() << __FUNCTION__;
//   switch(playerMode++)
//   {
//        case 0:     ui->PushButton_PlayMode->setIcon(QIcon(":/image/danquxunhuan.png"));
//                    ui->PushButton_PlayMode->setIconSize(QSize(48,48));
//                    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);          // 单曲循环
//        break;

//        case 1:     ui->PushButton_PlayMode->setIcon(QIcon(":/image/suijibofang.png"));
//                    ui->PushButton_PlayMode->setIconSize(QSize(48,48));
//                    playerList->setPlaybackMode(QMediaPlaylist::Random);                     // 随机播放
//        break;

//        case 2:     ui->PushButton_PlayMode->setIcon(QIcon(":/image/yinlebofangye-xunhuanbofang.png"));
//                    ui->PushButton_PlayMode->setIconSize(QSize(48,48));
//                    playerList->setPlaybackMode(QMediaPlaylist::Loop);                       // 循环播放
//        break;
//   }
//   if(playerMode == 3)  playerMode = 0;
}

// 删除歌曲
void AudioPlay::on_PushButton_DeleteMusic_clicked()
{
//    qDebug() << __FUNCTION__;
//    if(playerList->mediaCount() == 0) return;

//    configIniDelete = new QSettings("PlayList.ini",QSettings::IniFormat);
//    int curPlayIndex = ui->tableWidget->currentRow();
//    if( curPlayIndex >= 0)
//    {
//        for (int i = curPlayIndex; ; i++)
//        {
//            if(configIniDelete->value("/song/"+QString::number(i+1),100).toInt() != 100) //
//            {
//                configIniDelete->setValue("/song/"+QString::number(i),configIniDelete->value("/song/"+QString::number(i+1)).toString());
//            }
//            else
//            {
//                configIniDelete->remove("/song/"+QString::number(i));
//                break;
//            }
//        }
//       playerList->removeMedia(curPlayIndex);
//       ui->tableWidget->removeRow(curPlayIndex);
//    }
      int pos=ui->tableWidget->currentRow();
      if(pos>=0){
          QString str = ui->tableWidget->item(pos,0)->text();

          QSettings* fileset=new QSettings("D:/PlayList.ini", QSettings::IniFormat);
          QString name=fileset->value("/song/"+str).toString();
          fileset->remove("/song/"+str);
          ui->tableWidget->removeRow(pos);

          //将playList和fileList中对应的项也删掉
          playList.removeOne(str);
          fileList.removeOne(name);
      }
}




bool AudioPlay::eventFilter(QObject *obj, QEvent *e)
{
//    qDebug() << __FUNCTION__;
    if (obj == ui->centralWidget)
    {
        if(e->type() == QEvent::MouseButtonDblClick)
        {
            on_pushButton_WindowMax_clicked();
            return true;
        }
    }
    return QObject::eventFilter(obj, e);
}

void AudioPlay::mousePressEvent(QMouseEvent *e)//鼠标按下事件
{
    qDebug() << __FUNCTION__;
    if (e->button() == Qt::LeftButton)
    {
        mDrag = true;
        mDragPos = e->globalPos() - pos();
        e->accept();
    }
}

void AudioPlay::mouseMoveEvent(QMouseEvent *e)//鼠标移动事件
{
    qDebug() << __FUNCTION__;
    if (mDrag && (e->buttons() && Qt::LeftButton))
    {
        move(e->globalPos() - mDragPos);
        e->accept();
    }
}

void AudioPlay::mouseReleaseEvent(QMouseEvent *e)//鼠标释放事件
{
    qDebug() << __FUNCTION__;
    mDrag = false;
}


void AudioPlay::on_pushButton_WindowMin_clicked()
{
    showMinimized();
}

void AudioPlay::on_pushButton_WindowMax_clicked()
{
    if (mIsMax)
       {
            //新增两行代码
            //setWindowFlags(Qt::Window);
            showFullScreen();
            //setGeometry(mLocation);


//           ui->pushButton_WindowMax->setIcon(QIcon(":/image/max1.png"));
//           ui->pushButton_WindowMax->setToolTip(QStringLiteral("最大化"));
       }
       else
       {
            //setWindowFlags(Qt::Widget);
            showNormal();
            //mLocation = geometry();
           //setGeometry(qApp->desktop()->availableGeometry());
//           ui->pushButton_WindowMax->setIcon(QIcon(":/image/max2.png"));
//           ui->pushButton_WindowMax->setToolTip(QStringLiteral("还原"));
       }
       mIsMax = !mIsMax;

}

void AudioPlay::on_pushButton_WindowExit_clicked()
{
    qApp->exit();
}


//接受拖拽的文件
void AudioPlay::dragEnterEvent(QDragEnterEvent * event)
{
    qDebug()<<__FUNCTION__;
    event->acceptProposedAction();    //接受拖拽的文件
}

// 获取拖拽的文件名
void AudioPlay::dropEvent(QDropEvent * event)
{
    qDebug()<<__FUNCTION__;

    QString fileInfo;
    QFileInfo  Info;
    bool status = false;

    auto urls = event->mimeData()->urls();
    for(auto it = urls.begin();it != urls.end();++it)    //获取拖拽的文件名
    {
        fileInfo = it->toLocalFile();
        Info = QFileInfo(it->toLocalFile());

        qDebug()<<it->toLocalFile();
    }

    QString fileName = Info.completeBaseName(); //  文件名不带后缀
    QString fileSuffix = Info.suffix(); //  文件后缀

    // list << "*.mp3" << "*.wav" << "*.wma" << "*.flac" << "*.wmv" << "*.mp4" << "*.mov" << "*.avi" ;
    if(fileSuffix != "mp3" &&
       fileSuffix != "wav"  &&
       fileSuffix != "wma"  &&
       fileSuffix != "flac" &&
       fileSuffix != "wmv"  &&
       fileSuffix != "mp4"  &&
       fileSuffix != "mov"  &&
       fileSuffix != "avi"
       ) return;

//    if(playerList->mediaCount() > 0)
//    {
//        for (int i = 0;i < playerList->mediaCount() ; i++)
//        {
//            QString songName = ui->tableWidget->item(i,0)->text();         //  取出字符串
//            if(songName == fileName + "." + fileSuffix)              // 判断是否是重复添加歌曲
//            {
//                status = true;
//                break;
//            }
//        }

//    }

//    if(status == false)
//    {

//        playerList->addMedia(QUrl(fileInfo));       // 把扫描得到的歌曲添加到播放列表上。带路径的

//        int rownum = ui->tableWidget->rowCount();
//        ui->tableWidget->insertRow(rownum);
//        ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem(fileName + "." + fileSuffix));

//        configIniWrite->setValue("/song/"+QString::number(rownum), fileInfo); // 保存歌曲列表
//        player->setPlaylist(playerList); // 把播放列表添加到播放器
//        playMusic(rownum);
//    }

}

void AudioPlay::on_Slider_Volume_actionTriggered(int action)
{

}

void AudioPlay::on_Slider_Volume_sliderMoved(int position)
{

}

void AudioPlay::on_Slider_ProgressBar_sliderPressed()
{
    mDrag=true;
}
