#include "sandbox.h"

void Sandbox::show(int *pixels) {
    if (pixels == 0) {
        // show current src image
        form->scene->addPixmap(imagePixmap);
    } else {
        QImage* image = new QImage(imagePixmap.width(), imagePixmap.height(), QImage::Format_ARGB32);

        for (int y = 0; y < imagePixmap.height(); y++)
            for (int x = 0; x < imagePixmap.width(); x++)
                image->setPixelColor(x,y, pixels[y * imagePixmap.width() + x]);
        form->scene->addPixmap(QPixmap::fromImage(*image));
    }
    form->showMaximized();
}
void Sandbox::getImageViaFileDialog() {

    fileName = QFileDialog::
            getOpenFileName(NULL,
                            "Open Image", IMAGES_PATH, "Image Files (*.png *.jpg *.bmp)");
    imagePixmap.load(fileName);
}
void Sandbox::write(int *pixels) {
    QImage image = imagePixmap.toImage();

    for (int y = 0; y < imagePixmap.height(); y++)
        for (int x = 0; x < imagePixmap.width(); x++)
            image.setPixelColor(x,y, pixels[y * imagePixmap.width() + x]);

    QFile file("newImage.png");
    file.open(QIODevice::WriteOnly);
    image.save(&file, "PNG");
}

int* Sandbox::gaussianFilter() {
    double sigma = 7;
    int size = floor(3 * sigma);
    double* kernel =  Helper::gauss(sigma);

    ConvolutionalTool* tool = new ParallelConvolutionalTool(imagePixmap.width(),
                                                            imagePixmap.height(),
                                                            kernel,
                                                            size);

    DataRetriver dr = DataRetriver(NULL);

    int* data = dr.retriveData(imagePixmap);
    int * result = tool->process(BORDER, R | G | B | A, data);
    show(result);
    return result;
}
int* Sandbox::increaseSharpness() {
    double INCREASE_SHARPNESS[] =  {
        -1.0, -1.0, -1.0,
        -1.0, 9.0, -1.0,
        -1.0, -1.0, -1.0
    };

    int size = 3;


    ConvolutionalTool* tool = new ParallelConvolutionalTool(imagePixmap.width(),
                                                            imagePixmap.height(),
                                                            INCREASE_SHARPNESS,
                                                            size);

    DataRetriver dr = DataRetriver(NULL);

    int* data = dr.retriveData(imagePixmap);
    int * result = tool->process(BORDER, R | G | B | A, data);
    show(result);
    return result;
}
int* Sandbox::sobelOperator() {
    double SOBEL_X[] =  {
        1.0, 0, -1.0,
        2.0, 0, -2.0,
        1.0, 0, -1.0
    };
    double SOBEL_Y[] =  {
        1.0, 2.0, 1.0,
        0.0, 0.0, 0.0,
        -1.0, -2.0, -1.0
    };
    int * result = 0;

    return result;
}
