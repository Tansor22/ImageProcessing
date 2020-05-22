//
// Created by Sergei on 22.05.2020.
//

#include "Rotate.h"

QPixmap Rotate::distort(QPixmap pixmap) {
    QMatrix rm;
    rm.rotate(degrees);
    return pixmap.transformed(rm);
}
