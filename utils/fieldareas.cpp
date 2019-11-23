#include "fieldareas.h"

namespace FieldAreas {
bool hasArea(FieldArea fieldArea, FieldArea hasArea) {
    return (fieldArea & hasArea);
}
FieldArea addArea(FieldArea fieldArea, FieldArea areaToAdd) {
    return static_cast<FieldArea>(fieldArea | areaToAdd);
}
FieldArea delArea(FieldArea fieldArea, FieldArea areaToDel) {
    return static_cast<FieldArea>(fieldArea & ~areaToDel);
}
}