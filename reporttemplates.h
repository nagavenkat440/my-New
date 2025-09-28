#ifndef REPORTTEMPLATES_H
#define REPORTTEMPLATES_H

#include <QMap>
#include <QString>

class ReportTemplates
{
public:
    static QString Ate_Self_Test_Report();

    static QString Bit_Test_Report();
    static QString LRU_Test_Report();
    static QString DC_DC_Report();
    static QString cntrl_cards();
    static QString FTU_LRUChecks();

    //    static QString voltageHtml();
    //    static QString loadHtml();
    //    static QString RippleHtml();

    //    static QString cntrl_checksum();
    //    static QString cntrl_voltagechecks();
    //    static QString cntrl_Abort_Ready_Init_PrepChecks();
    //    static QString cntrl_AnalogChecks();
    //    static QString FTU_LRU_AnalogChecks();
    //    static QString FTU_LRU_ESS_QTChecks();
    static QString populateTemplate(const QString &templateHtml,
                                    const QMap<QString, QString> &params);
};

#endif // REPORTTEMPLATES_H
