#ifndef AUTOCELL_H
#define AUTOCELL_H


#include <QThread>
#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include "automate.h"
#include "xml_dom.h"
#include "autocellmere.h"
k:khqglkushfd;gkhsef:jsfd
dsfshdf;jbhsfgb
skhj;sghskf
/*!
 * \brief The AutoCell class permet de créer des automates 1D
 */
class AutoCell : public AutoCellmere{
Q_OBJECT
    /*!
     * \brief num numero de règle int
     */
    QSpinBox* num;
    /*!
     * \brief numeroBit numero regle bit
     */
    QLineEdit* numeroBit[8];
    QLabel* r;
    QLabel* numl;
    QLabel* numeroBitl[8];
    QVBoxLayout* numc;
    QVBoxLayout* bitc[8];
    QHBoxLayout* numeroc;
    QHBoxLayout* roc;
    /*!
     * \brief dimension dimension matrice 1d
     */
    unsigned int dimension;
    unsigned int test;

public:
explicit AutoCell(QWidget* parent = nullptr, unsigned int i=10);
private slots:
void setNum();
void synchronizeNumToNumBit(int i);
void synchronizeNumBitToNum();
void cellActivation(const QModelIndex& index);
void faireSimulation();
void reset();
void reset2();
void genaleatoire();
void b2_clicked();
void b5_clicked();
void xml();
};
#endif // AUTOCELL_H
