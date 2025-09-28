// reportgenerator.cpp
#include "reportgenerator.h"
#include "QDebug"
#include "QMessageBox"
#include <QFile>
#include <QFileInfo>
#include <QPrinter>
#include <QProcess>
#include <QTextDocument>
#include <QTextStream>

ReportGenerator::ReportGenerator(QObject *parent)
    : QObject(parent)
{}
/*
void ReportGenerator::generateReport(const QString &htmlContent,
                                     const QString &pdfPath,
                                     const QString &odtPath)
{
//    QTextDocument document;
//    document.setHtml(htmlContent);
//    saveAsPDF(&document, pdfPath);

QString htmlPath = pdfPath;
htmlPath.replace(".pdf", ".html");
QFile htmlFile(htmlPath);
if (htmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&htmlFile);
    out << htmlContent;
    htmlFile.close();
}

convertToODT(htmlPath, odtPath);
}
*/

void ReportGenerator::generateReport(const QString &htmlContent, const QString &pdfPath)
{
    QString htmlPath = pdfPath;
    htmlPath.replace(".pdf", ".html");

    // Save HTML to file
    QFile htmlFile(htmlPath);
    if (htmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&htmlFile);
        out << htmlContent;
        htmlFile.close();
    } else {
        qWarning() << "Could not write HTML to file:" << htmlPath;
        return;
    }

    // === PDF GENERATION USING WKHTMLTOPDF ===
    QString wkhtmlPath = "C:/Program Files/wkhtmltopdf/bin/wkhtmltopdf.exe";
    if (!QFileInfo::exists(wkhtmlPath)) {
        qWarning() << "wkhtmltopdf.exe not found at:" << wkhtmlPath;
        QMessageBox::critical(nullptr,
                              "Error",
                              "wkhtmltopdf.exe not found.\nPlease install it or fix the path:\n"
                                  + wkhtmlPath);
        return;
    }

    QStringList pdfArgs;
    pdfArgs << "--enable-local-file-access" << htmlPath << pdfPath;

    QProcess pdfProcess;
    pdfProcess.start(wkhtmlPath, pdfArgs);
    pdfProcess.waitForFinished(-1);

    if (pdfProcess.exitStatus() == QProcess::NormalExit && pdfProcess.exitCode() == 0) {
        //        qDebug() << "PDF generated at:" << pdfPath;
    } else {
        qWarning() << "PDF generation failed:" << pdfProcess.readAllStandardError();
    }

    // === ODT GENERATION USING LIBREOFFICE ===
    //    QString libreOfficePath = "C:/Program Files/LibreOffice/program/soffice.exe"; // Adjust if needed
    //    if (!QFileInfo::exists(libreOfficePath)) {
    //        qWarning() << "LibreOffice not found at:" << libreOfficePath;
    //        QMessageBox::critical(nullptr,
    //                              "Error",
    //                              "LibreOffice not found.\nPlease install it or fix the path:\n"
    //                                  + libreOfficePath);
    //        return;
    //    }

    //    QString odtOutputDir = QFileInfo(odtPath).absolutePath();

    //    QStringList odtArgs;
    //    odtArgs << "--headless"
    //            << "--convert-to"
    //            << "odt" << htmlPath << "--outdir" << odtOutputDir;

    //    QProcess odtProcess;
    //    odtProcess.start(libreOfficePath, odtArgs);
    //    odtProcess.waitForFinished(-1);

    //    if (odtProcess.exitStatus() == QProcess::NormalExit && odtProcess.exitCode() == 0) {
    //        qDebug() << "ODT generated at:" << odtPath;
    //    } else {
    //        qWarning() << "ODT generation failed:" << odtProcess.readAllStandardError();
    //    }

    //    // Optionally: QFile::remove(htmlPath); // delete intermediate HTML
}

#if 0
void ReportGenerator::saveAsPDF(QTextDocument *document, const QString &pdfPath)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdfPath);
    document->print(&printer);
}

void ReportGenerator::convertToODT(const QString &htmlPath, const QString &odtPath)
{
    QStringList args;
    args << "--headless"
         << "--convert-to"
         << "odt" << htmlPath << "--outdir" << QFileInfo(odtPath).absolutePath();
    QProcess::execute("libreoffice", args);
}
#endif
