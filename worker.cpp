#include "worker.h"
#include "ffmpeg.h"
#include"audio.h"
#include <QList>
#include <QDebug>
#include <QTime>

worker::worker()
{
    filename="";
    isStop=true;
    isPause=false;
    isChanged=false;
    isExit=false;
    audioPts=0;
    errCount=0;
    vList.clear();
    slidown=false;
}
worker::~worker()
{

}

void worker::run() {  //该线程负责的工作就是读取视频的每一帧，然后解码，将解码的Frame放到v/a List 中给主线程使用
    char out[10000] = {0};
    int countN=0;
    while(!isExit){
        while(!isStop){
            if (isPause==true)//如果为暂停状态，不处理
            {
                if(slidown==true){
                    vList.clear();
                    slidown=false;
                    msleep(200);
                }
                msleep(50);
                continue;
                qDebug()<<"A";
            }

            if(isChanged==true){  //播放的视频改变了
                isChanged=false;
                //char* str=filename.toLatin1().data();
                //qDebug()<<str;
                while(ffmpeg::get()->readFile(filename)<0){
                    msleep(10);
                }

                memset(out,0,sizeof(out));

                //清空视频队列
                vList.clear();
                XAudioPlay::Get()->Start();
                audioPts=0;
                msleep(20);
                continue;
            }

            while (vList.size() > 0)//确定list中是否有视频帧
            {
                qDebug()<<"length:  "<<vList.size();
                AVFrame vfr = vList.front().vFrame;//每次取出list中的第一个AVPack包
                //int pts = XFFmpeg::Get()->GetPts(&pack);//获得该包的pts
                double pts=vList.front().pts;
                qDebug()<<"PPPPPPPPPPPPPPPPPPPPPPP"<<pts<<"     "<<ffmpeg::get()->m_totalMs;
                if (pts > audioPts)//若视屏包大于音频包的pts，结束
                {
                    qDebug()<<"音频先   "<<pts<<"      "<<audioPts;
                    break;
                }
                qDebug()<<"视频先    "<<pts<<"      "<<audioPts;;
                QImage img=ffmpeg::get()->toRGB(&vfr);
                vList.pop_front();//从list链表中删除
                emit sig_Send(img,pts);
            }

            int free = XAudioPlay::Get()->GetFree();//此时缓冲区的空间大小
            if (free < 10000)
            {
                msleep(1);
                continue;
            }
            AVPacket pkt = ffmpeg::get()->readPacket();
            ++countN;
            qDebug()<<"countN:  "<<countN;
            if (pkt.size <= 0)//未打开视频
            {
                ++errCount;
                if(errCount>=15){
                    isStop=true;
                    errCount=0;
                    emit sig_End();
                    continue;
                }
                msleep(5);
                continue;
            }
            if (pkt.stream_index == ffmpeg::get()->m_audioStream)
            {
                qDebug()<<"AUDIO";
                audioPts = ffmpeg::get()->decodePacket(&pkt);//解码音频
                av_packet_unref(&pkt);//释放pkt包S
                int len = ffmpeg::get()->toPCM(out,ffmpeg::get()->m_PpcmFrame);//重采样音频
                //audioPts= ffmpeg::get()->getAudioPTS(ffmpeg::get()->m_PpcmFrame,&pkt,len,XAudioPlay::Get()->io->size());
                XAudioPlay::Get()->Write(out, len);//写入音频
                emit audio_send(audioPts);
                continue;
            }else if(pkt.stream_index == ffmpeg::get()->m_videoStream){
                qDebug()<<"VEDIO";
                vedio_frame* vf=new vedio_frame();
                vf->pts=ffmpeg::get()->decodePacket(&pkt);
                //vf->pts=ffmpeg::get()->getVideoPTS(ffmpeg::get()->m_PyuvFrame,&pkt);

                vf->vFrame=*ffmpeg::get()->m_PyuvFrame;
                vList.push_back(*vf);
            }
            av_packet_unref(&pkt);//清理该AVPacket包
        }

//        if (isPause==true)//如果为暂停状态，不处理
//        {
//            msleep(50);
//            continue;
//            qDebug()<<"A";
//        }
//        int fps=0;
//        qDebug()<<"B";
//        AVPacket pkt = ffmpeg::get()->readPacket();
//        if (pkt.size <= 0)//未打开视频
//        {
//            msleep(10);
//            qDebug()<<"C";
//            continue;
//        }
//        qDebug()<<"D";
//        if(pkt.stream_index==ffmpeg::get()->m_videoStream){
//            isVedio=true;
//            qDebug()<<"E";
//        }else{
//            isVedio=false;
//            qDebug()<<"F";
//        }
//        fps=ffmpeg::get()->decodePacket(&pkt);
//        av_packet_unref(&pkt);//释放pkt包
//        qDebug()<<"G";
//        if(isVedio==true){
//            vedio_frame* vf=new vedio_frame();
//            vf->pts=fps;
//            vf->vFrame=*ffmpeg::get()->m_PyuvFrame;
//            mutex.lock();

//            vList.push_back(*vf);
//            qDebug()<<"Worker VVV size=="<<vList.size();

//            mutex.unlock();
//            qDebug()<<"H";
//        }else{
//            audio_frame* af=new audio_frame();
//            af->pts=fps;
//            af->aFrame=*ffmpeg::get()->m_PpcmFrame;
//            mutex.lock();

//            aList.push_back(*af);
//            qDebug()<<"Worker AAA size=="<<aList.size();
//            mutex.unlock();
//            qDebug()<<"J";
//        }
//        msleep(15);
    }
}
