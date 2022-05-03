#include "../mainwindow.hpp"

#include <QFileDialog>
#include <QSettings>
#include <QDir>

#include "common/dataIdentifiers.hpp"

void MainWindow::readNewFlightplan()
{

    QFileDialog dialog;
    QString lastUsedDir = QSettings().value("lastUsedDir", QDir::homePath() + "/AppData/Roaming/Microsoft Flight Simulator").toString();
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory(lastUsedDir);
    dialog.setNameFilter("pln files (*.PLN *.pln)");

    if (dialog.exec() != 0)
    {
        QString selectedDir = dialog.directory().absolutePath();
        QString selectedFile = dialog.selectedFiles().at(0);
        QSettings().setValue("lastUsedDir", selectedDir);
        readFlightplan(selectedFile);
    }
}
