#ifndef CSORTER_H
#define CSORTER_H

#include <CBase4618.h>


class CSorter : public CBase4618
{
    public:
        CSorter();
        virtual ~CSorter();
        void run();
    protected:

    private:
    void update();
    void draw();

};

#endif // CSORTER_H
