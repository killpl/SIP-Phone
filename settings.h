#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "settings.h"

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT
    
public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    
private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
