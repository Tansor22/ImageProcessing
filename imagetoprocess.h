#ifndef IMAGETOPROCESS_H
#define IMAGETOPROCESS_H
#include <QPixmap>
#include <constants.h>
#include <dataretriver.h>
#include <helper.h>
#include <pointofinterest.h>
#include "poishandler.h"
#include "sequentialconvolutiontool.h"
#include "parallelconvolutiontool.h"
#include "KernelsHandler.h"


class ImageToProcess
{

public:
    static QString PATH_TO_SAVE;
    enum OutOfBoundPolicy {
        EDGE,
        BLACK,
        WHITE,
        SPREAD
    };
    ImageToProcess();
    //~ImageToProcess();
    // copy constructor
    ImageToProcess(const ImageToProcess &itp);
    // = overload
    ImageToProcess &operator=(const ImageToProcess itp);
    ImageToProcess(Canal type, double* data, int w, int h);
    ImageToProcess(QPixmap Pixmap, Canal type);
    explicit ImageToProcess(ImageToProcess *itp, OutOfBoundPolicy = EDGE);
    ImageToProcess(ImageToProcess *itp, Canal type);
    ImageToProcess(Canal type, int w, int h);
    double shiftError(int winSize, int x, int y, int dx, int dy);
    double getValueSafe(int x, int y);
    double operator[](int i) const;
    void setValueSafe(int x, int y, double value);
    void setValueSafe(int x, int y, QRgb rgb);
    void setDoubles(Canal t, double* dD, int W, int H);
    QRgb* toIntRGB();
    QImage toQImage();
    void derivativeX();
    void save(QString fileName);
    void cross(double* kernel, int kernelW, int kernelH, double divider = 1.0);
    void gaussBlur(double sigma);
    void derivativeY();
    void gradient();
    QList<PointOfInterest> getPOIs(int winSize, bool isHarris = false);
    QList<PointOfInterest> filterPOIs(QList<PointOfInterest> pointsIn, int count);
    void downSample();
    void save();

    // vars
    double* doubleData;
    int w = 0;
    int h = 0;
    Canal type;
    OutOfBoundPolicy oobp = EDGE;
    std::string name = "";


    int getW() const;
    int getH() const;
    double *getDoubles() const;
    Canal getType() const;
    void setType(const Canal &value);
    void setName(const std::string &value);
};

#endif // IMAGETOPROCESS_H
