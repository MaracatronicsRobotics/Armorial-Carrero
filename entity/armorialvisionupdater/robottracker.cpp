#include "robottracker.h"
RobotTracker::RobotTracker() {
    _associations.insert(Colors::BLUE, new QMap<quint8,Position>());
    _associations.insert(Colors::YELLOW, new QMap<quint8,Position>());
    _associated.insert(Colors::BLUE, new QList<quint8>());
    _associated.insert(Colors::YELLOW, new QList<quint8>());
}
RobotTracker::~RobotTracker() {
    delete _associations.value(Colors::BLUE);
    delete _associations.value(Colors::YELLOW);
    delete _associated.value(Colors::BLUE);
    delete _associated.value(Colors::YELLOW);
}
void RobotTracker::startAssociations() {
    _associated.value(Colors::BLUE)->clear();
    _associated.value(Colors::YELLOW)->clear();
}
quint8 RobotTracker::getId(const Position &position, Colors::Color teamColor) {
    // If first association
    if(_associations.value(teamColor)->empty())
        return generateAssociation(position, teamColor);
    // Check if already associated
    quint8 id=0;
    if(isAssociated(position, teamColor, &id)) {
        _associations.value(teamColor)->insert(id, position);
        _associated.value(teamColor)->append(id);
        return id;
    } else {
        return generateAssociation(position, teamColor);
    }
}
void RobotTracker::endAssociations() {
    // Check positions not associated
    for(int color=Colors::YELLOW; color<=Colors::BLUE; color++) {
        for(int i=0; i<_associations.value(color)->size(); i++) {
            const quint8 assocId = _associations.value(color)->keys().at(i);
            if(_associated.value(color)->contains(assocId)==false)
                _associations.value(color)->remove(assocId);
        }
    }
}
bool RobotTracker::isAssociated(const Position &position, Colors::Color teamColor, quint8 *id) {
    float minDist = 999;
    qint8 minDistAssocId=-1;
    // Run on associations and get closer (with max dist check)
    QMap<quint8,Position>::iterator it;
    for(it=_associations.value(teamColor)->begin(); it!=_associations.value(teamColor)->end(); it++) {
        const quint8 assocId = it.key();
        const Position assocPos = it.value();
        // Check already associated
        if(_associated.value(teamColor)->contains(assocId))
            continue;
        // Dist to position
        float dist = sqrt(pow((position.x() - assocPos.x()), 2) + pow((position.y() - assocPos.y()), 2));
        // Check max dist
        if(dist>MAX_DIST_ASSOCIATION)
            continue;
        // Check min
        if(dist<minDist) {
            minDist = dist;
            minDistAssocId = assocId;
        }
    }
    // Return associated
    if(minDistAssocId==-1)
        return false;
    else {
        *id = minDistAssocId;
        return true;
    }
}
quint8 RobotTracker::generateAssociation(const Position &position, Colors::Color teamColor) {
    quint8 newId=0;
    // Search a free id
    QList<quint8> ids = _associations.value(teamColor)->keys();
    for(quint8 i=0; i<MAX_ROBOTS; i++) {
        if(i>=ids.size() || (i<ids.size() && i!=ids.at(i))) {
            newId = i;
            break;
        }
    }
    // Associate
    _associations.value(teamColor)->insert(newId, position);
    _associated.value(teamColor)->append(newId);
    return newId;
}