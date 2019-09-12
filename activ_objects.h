#ifndef ACTIV_OBJECTS_H
#define ACTIV_OBJECTS_H

#include <memory>
#include <thread>
#include <condition_variable>
#include <queue>
template<typename TT>
class message_queue
{//
    std::mutex m;
    std::condition_variable c;
    std::queue<TT> q;  ///здесь храняться указатели на message_base
public:
    template<typename T> void push(T const& msg)    {
        std::lock_guard<std::mutex> lk(m);
        q.push(msg);
        c.notify_all();
    }
    auto wait_and_pop()    {
        std::unique_lock<std::mutex> lk(m);
        if(!q.empty()){
            auto res = q.front();
            q.pop();
            //std::printf(" 0  queue size:     %d\n",q.size());
            return res;
        }else{
            c.wait(lk,[&]{return !q.empty();});/// блокирует до появления в очереди xотябы одного элемента
            auto res = q.front();
            q.pop();
            //std::printf(" 1  queue size:     %d\n",q.size());
            return res;
        }
    }
};


class Activ_objects
{
public:

  class Message {// base of all message types
  public:
    Message(){}
    Message(const Message& othre)               =default;//{  }
    Message(Message&& othre)                    =default;//{ }
    Message& operator = (const Message& othre)  =default;//{  }
    Message& operator = (Message&& othre)       =default;//{ }

    virtual ~Message() { }
    virtual void Execute() { }
  };

  // b_start everything up, using Run as the thread mainline
  Activ_objects() :
    done( new Message ) {
    thd = std::unique_ptr<std::thread>( new std::thread(&Activ_objects::Run, this) );
  }

  // Shut down: send sentinel and wait for queue to drain
  ~Activ_objects() {
    //Send( done );
    thd->join();
  }

private:
  std::unique_ptr<Message> done;               // le sentinel
  message_queue<std::unique_ptr<Message> > mq;  // le queue
  std::unique_ptr<std::thread> thd;            // le thread

private:
  // The dispatch loop: pump messages until done
  void Run() {
    std::unique_ptr<Message> msg;
//    while( (msg = mq.receive()) != done ) {
//      msg->Execute();
//    }
  }

public:

  // Enqueue a message
  void Send(std::unique_ptr<Message> m ) {
   // mq.send( m );
  }

};



/*

http://www.drdobbs.com/parallel/prefer-using-active-objects-instead-of-n/225700095?pgno=2

class Backgrounder {
public:
  void Save( string filename ) {
    a.Send( new MSave( this, filename ) );
  }

  void Print( Data& data ) {
    a.Send( new MPrint( this, data ) );
  }

private:
  class MSave : public Active::Message {
    Backgrounder* this_;    string filename;
  public:
    MSave( Backgrounder* b, string f ) : this_(b), filename(f) { }
    void Execute() { … }    // do the actual work
  };

  class MPrint : public Active::Message {
    Backgrounder* this_;    Data& data;
  public:
    MPrint( Backgrounder* b, Data& d ) : this_(b), data(d) { }
    void Execute() { … }    // do the actual work
  };

  // Private state if desired
  PrivateData somePrivateStateAcrossCalls;

  // Helper goes last, for ordered destruction
  Active a;
};

*/
#endif // ACTIV_OBJECTS_H
