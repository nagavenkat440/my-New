// reportgenerator.h
#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QObject>
#include <QTextDocument>

class ReportGenerator : public QObject {
    Q_OBJECT

public:
    explicit ReportGenerator(QObject *parent = nullptr);
    void generateReport(const QString &htmlContent, const QString &pdfPath);

public slots:
private:
    void saveAsPDF(QTextDocument *document, const QString &pdfPath);
    void convertToODT(const QString &htmlPath, const QString &odtPath);
};

#endif // REPORTGENERATOR_H
