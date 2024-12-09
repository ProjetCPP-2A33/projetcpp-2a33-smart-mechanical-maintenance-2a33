#include "GraphView.h"
#include <QPainter>
#include <QPaintEvent>

GraphView::GraphView(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Graphique des services");
    resize(1200, 700); // Dimensions de la fenêtre
}

GraphView::~GraphView() {
    // Le destructeur peut être vide si aucune ressource n'est à libérer.
}

void GraphView::setData(const QMap<QString, int> &serviceData) {
    data = serviceData;
    update(); // Demande le redessin
}

void GraphView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Définir les marges et dimensions du graphique
    int margin = 150; // Marges des côtés
    int marginTop = 200; // Marges supérieures
    int width = this->width() - 2 * margin; // Largeur totale disponible pour les barres
    int height = this->height() - margin - marginTop; // Hauteur totale disponible pour les barres

    // Dessiner les axes
    painter.drawLine(margin, marginTop, margin, marginTop + height);        // Axe Y
    painter.drawLine(margin, marginTop + height, margin + width, marginTop + height); // Axe X

    // Calculer l'échelle
    int maxValue = 0;
    for (auto value : data.values()) {
        if (value > maxValue) maxValue = value;
    }

    // Réduire l'échelle (facteur multiplicateur)
    double scaleFactor = 0.3; // Réduire à 70% de l'échelle d'origine

    int barSpacing = 20; // Espacement entre les barres
    int barWidth = (width - (data.size() - 1) * barSpacing) / data.size();
    int x = margin;

    // Dessiner les barres
    int index = 0;
    for (auto it = data.begin(); it != data.end(); ++it) {
        int barHeight = static_cast<int>((static_cast<double>(it.value()) / maxValue) * height * scaleFactor);

        // Définir une couleur unique pour chaque barre
        QColor barColor = QColor::fromHsv((index * 60) % 360, 200, 255);
        painter.setBrush(barColor);

        // Dessiner la barre
        QRect barRect(x, marginTop + height - barHeight, barWidth, barHeight);
        painter.drawRect(barRect);

        // Agrandir la police
        QFont labelFont = painter.font();
        labelFont.setPointSize(9); // Taille plus grande pour une meilleure lisibilité
        painter.setFont(labelFont);

        // Incliner le texte des étiquettes
        painter.save();
        painter.translate(x + 5, marginTop + height + 40);
        painter.rotate(0); // Incliner de 45 degrés
        painter.drawText(0, 0, it.key()); // Texte incliné
        painter.restore();

        // Dessiner les valeurs
        painter.drawText(x + barWidth / 4, marginTop + height - barHeight - 10, QString::number(it.value()));

        x += barWidth + barSpacing; // Incrémente x avec largeur + espacement
        ++index;
    }
}
