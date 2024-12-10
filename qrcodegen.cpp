#ifndef QRCODEGEN_H
#define QRCODEGEN_H

#include <vector>
#include <string>

namespace qrcodegen {

class QrCode final {
public:
    // Error correction levels
    enum class Ecc {
        LOW,      // Plus de capacité, moins de correction
        MEDIUM,   // Équilibre entre correction et capacité
        QUARTILE, // Meilleure correction d'erreur
        HIGH      // Correction maximale
    };

    // Génère un QR Code à partir d'une chaîne de texte
    static QrCode encodeText(const char *text, Ecc ecl);

    // Renvoie la taille (en modules) du QR Code
    int getSize() const;

    // Renvoie true si le module (x, y) est noir
    bool getModule(int x, int y) const;

private:
    // Taille en modules
    int size;

    // Matrice du QR Code (true = noir, false = blanc)
    std::vector<std::vector<bool>> modules;

    // Constructeur privé (utilisé par encodeText)
    QrCode(int size, std::vector<std::vector<bool>> modules);
};

} // namespace qrcodegen

#endif // QRCODEGEN_H
