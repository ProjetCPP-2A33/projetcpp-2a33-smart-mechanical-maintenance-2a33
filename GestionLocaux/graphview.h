#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QDialog>
#include <QMap>
#include <QString>

namespace Ui {
class GraphView;
}

class GraphView : public QDialog
{
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);
    ~GraphView();

    void setData(const QMap<QString, int> &serviceData);  // Méthode pour mettre à jour les données

protected:
    void paintEvent(QPaintEvent *event) override;  // Méthode pour dessiner le graphique

private:
    QMap<QString, int> data;  // Contiendra les services et leur nombre d'occurrences
    int maxValue = 0;  // Valeur maximale pour l'échelle du graphique
};

#endif // GRAPHVIEW_H
