#ifndef FIELDAREAS_H
#define FIELDAREAS_H

namespace FieldAreas {
    enum FieldArea {
        Q1 = 1,
        Q2 = 1 << 1,
        Q3 = 1 << 2,
        Q4 = 1 << 3,
        RIGHT = Q1+Q4,
        LEFT = Q2+Q3,
        TOP = Q1+Q2,
        BOTTOM = Q3+Q4,
        ALL = RIGHT+LEFT
    };

    bool hasArea(FieldArea fieldArea, FieldArea hasArea);
    FieldArea addArea(FieldArea fieldArea, FieldArea areaToAdd);
    FieldArea delArea(FieldArea fieldArea, FieldArea areaToDel);
}


#endif // FIELDAREAS_H
