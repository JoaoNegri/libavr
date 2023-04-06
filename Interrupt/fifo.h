#ifndef __FIFO_H__
#define __FIFO_H__

template <typename T, int N>

class FIFO
{

private:
    T data[N];
    int in, out, size;

public:
    int put(T element)
    {
        if (this->size < N - 1 & this->in < N - 1)
        {
            this->data[this->in++] = element;
            this->size++;
        }
        else if (this->size < N - 1 & this->in == N - 1)
        {
            this->in = 0;
            this->data[this->in] = element;
            this->size++;
        }else{
            return -1;
        }
        return 0;
    }

    int get(T &info)
    {
        if (this->size > 0)
        {
            if (this->out<N - 1)
            {
                this->size--;
                info = this->data[this->out++];
                return 0;
            }
            else if (this->out == N - 1)
            {
                this->size--;
                this->out = 0;
                info = this->data[this->out];
                return 0;
            }
        }
        return -1;
    }

    int getSize(){
        return this->size;
    }

    FIFO() : in(0), out(0), size(0)
    {
    }
    ~FIFO(){
    }
};

#endif