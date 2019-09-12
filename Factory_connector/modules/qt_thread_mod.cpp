#include "qt_thread_mod.h"

#include <iostream>
#include <QString>
#include "factory_morf.h"

#define dbg() std::cout << __PRETTY_FUNCTION__ << "\n";

REGISTER_SERIALIZABLE(Qt_thread);

//Qt_thread* Qt_thread::self = nullptr;

Qt_thread::Qt_thread(QObject *pr) :
  QThread (pr)
{

//  self = this;

  readTimer.moveToThread(this);
  connect(&readTimer, SIGNAL(timeout()), SLOT(readTimeout()));

  dbg();
}

Qt_thread::~Qt_thread(){

  this->exit(0);

  if(p_usw != nullptr)
    delete p_usw;
  if(p_tsw != nullptr)
    delete p_tsw;
  if(p_aun != nullptr)
    delete p_aun;
  if(p_crd != nullptr)
//    delete p_crd;
//  if(p_tcw != nullptr)
//    delete p_tcw;
//  if(p_pix != nullptr)
//    delete p_pix;
//  if(p_fif != nullptr)
//    delete p_fif;

  dbg();

}

void Qt_thread::b_start(void *arg){
  dbg();
  if(arg!=nullptr){}
  this->start();
}

void Qt_thread::b_stop(void *arg){
  dbg();
  if(arg!=nullptr){}
  this->exit(0);
}

void Qt_thread::run(){

  readTimer.start(3000); /// без  exec(); безполезен

  try {

    dbg();

    /// фабрика объектов, все объекты знают о существовании друг друга

    // создадим сервер UDP
    QString str("4445");
    p_usw = dynamic_cast<Udp_sock_wrap*>(fm.create("Udp_sock_wrap"));    
    this->set_obj({"Udp_sock_wrap",p_usw}); ///
    p_usw->b_start(static_cast<void *>(&str));

    // создадим сервер TCP
    p_tsw = dynamic_cast<Tcp_server_wrap*>(fm.create("Tcp_server_wrap"));
    this->set_obj({"Tcp_server_wrap",p_tsw});
    p_tsw->b_start(static_cast<void *>(&str));

    // откроем arduino
    p_aun = dynamic_cast<Arduino_UNO*>(fm.create("Arduino_UNO"));
    this->set_obj({"Arduino_UNO",p_aun});
    p_aun->b_start(static_cast<void *>(&str));

    p_crd = dynamic_cast<Console_Reader*>(fm.create("Console_Reader"));
    this->set_obj({"Listen_std_in",p_crd});
    p_crd->b_start(static_cast<void *>(&str));

    // откроем PIX
    p_pix = dynamic_cast<Pix4_serial*>(fm.create("Pix4_serial"));
    this->set_obj({"Pix4_serial",p_pix});
    QString pix_op("/dev/ttyACM0");
    p_pix->b_start(static_cast<void *>(&pix_op)); /////
    pix_op = std::move(QString("/dev/ttyACM1"));  /// временный объект не перемещается
    p_pix->b_start(static_cast<void *>(&pix_op)); /////

    // откроем каналы fifio
    QVector<QString> v_str{ "/dev/tty-from-bpla-to-pix",  //
                            "/dev/tty-from-pix-to-bpla"}; //
    p_fif = dynamic_cast<Fifo_mod*>(fm.create("Fifo_mod"));
    this->set_obj({"Fifo_mod",p_fif});
    p_fif->b_start(static_cast<void *>(&v_str));


    //dbg();
    exec();
   //  while(1){   sleep(1);   }
  } catch (std::exception &ex) {
    std::cout << __FILE__ << " " << __LINE__ << " " << ex.what() << "\n";
    terminate();
  }

  readTimer.stop();

}


//bool Qt_thread::event(QEvent *evt){

//  this->QObject::event(evt);
//  std::cout <<__PRETTY_FUNCTION__ << " " << evt->type() << " \n";

//}


void Qt_thread::readTimeout(){
  //std::time_t t = std::time(0);   // get time now
  //std::tm* now = std::localtime(&t);
  //std::cout << (now->tm_year + 1900) << ':' << (now->tm_mon + 1) << ':' <<  now->tm_mday << '_' << (now->tm_hour) << ':' << (now->tm_min) << ':' << (now->tm_sec) << "\n";
 // std::cout << t <<  " seconds since the Epoch "  << std::asctime(std::localtime(&t));
  //std::cout << "UTC  :     " << std::put_time(std::gmtime(&t), "%c %Z") << '\n';
  //std::cout << "local:     " << std::put_time(std::localtime(&t), "%c %Z") << '\n';
}

void Qt_thread::b_start_new_thread(){

  //invoce decay
  //vec_thread.push_back(QThread::create([](int arg){ std::cout << __PRETTY_FUNCTION__ << "\n"; }));
  //vec_thread.back()->b_start();

}

void Qt_thread::b_stop_thread(){

  //vec_thread.back()->exit();
  //delete vec_thread.back();
  //vec_thread.pop_back();

}
