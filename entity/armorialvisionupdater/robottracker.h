#ifndef ROBOTTRACKER_HH
#define ROBOTTRACKER_HH
#include <GEARSystem/Types/types.hh>
#include <utils/color.h>
#define MAX_DIST_ASSOCIATION 0.20
#define MAX_ROBOTS 6
class RobotTracker {
private:
    QHash<int,QMap<quint8,Position>* > _associations;
    QHash<int,QList<quint8>* > _associated;
    bool isAssociated(const Position &position, Colors::Color teamColor, quint8 *id);
    quint8 generateAssociation(const Position &position, Colors::Color teamColor);
public:
    RobotTracker();
    ~RobotTracker();
    void startAssociations();
    quint8 getId(const Position &position, Colors::Color teamColor);
    void endAssociations();
};
#endif // ROBOTTRACKER_HH