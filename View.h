#ifndef VIEW_H
#define VIEW_H

#include <string>

class View {
public:
    int showMenu() const;
    int askMonth() const;
    int askYear() const;

    void showMessage(const std::string& message) const;
};

#endif
