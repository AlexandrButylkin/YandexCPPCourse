#ifndef TASK_6_GAMEOBJECT_H
#define TASK_6_GAMEOBJECT_H

class Unit;
class Building;
class Tower;
class Fence;

struct GameObject {
    virtual ~GameObject() = default;

    virtual bool Collide(const GameObject& that) const = 0;

    virtual bool CollideWith(const Unit& that) const = 0;
    virtual bool CollideWith(const Building& that) const = 0;
    virtual bool CollideWith(const Tower& that) const = 0;
    virtual bool CollideWith(const Fence& that) const = 0;
};

template <typename T>
class Collider : public GameObject {
    bool Collide(const GameObject &that) const final {
        return that.CollideWith(static_cast<const T&>(*this));
    }
};

class Unit : public Collider<Unit>{
public:
    explicit Unit(geo2d::Point position) : position_(position) {}

    bool CollideWith(const Building &that) const override;
    bool CollideWith(const Fence &that) const override;
    bool CollideWith(const Tower &that) const override;
    bool CollideWith(const Unit &that) const override;
    const geo2d::Point GetUnit() const;

private:
    geo2d::Point position_;
};

class Building : public Collider<Building>{
public:
    explicit Building(geo2d::Rectangle geometry) : geometry_(geometry){}

    bool CollideWith(const Building &that) const override;
    bool CollideWith(const Fence &that) const override;
    bool CollideWith(const Tower &that) const override;
    bool CollideWith(const Unit &that) const override;
    geo2d::Rectangle GetBuilding() const;

private:
    geo2d::Rectangle geometry_;
};

class Tower : public Collider<Tower>{
public:
    explicit Tower(geo2d::Circle geometry) : geometry_(geometry) {}

    bool CollideWith(const Building &that) const override;
    bool CollideWith(const Fence &that) const override;
    bool CollideWith(const Tower &that) const override;
    bool CollideWith(const Unit &that) const override;
    const geo2d::Circle GetTower() const;

private:
    geo2d::Circle geometry_;
};

class Fence : public Collider<Fence>{
public:
    explicit Fence(geo2d::Segment geometry) : geometry_(geometry) {}

    bool CollideWith(const Building &that) const override;
    bool CollideWith(const Fence &that) const override;
    bool CollideWith(const Tower &that) const override;
    bool CollideWith(const Unit &that) const override;
    const geo2d::Segment GetFence() const;

private:
    geo2d::Segment geometry_;
};




bool Unit::CollideWith(const Building &that) const {
    return geo2d::Collide(position_, that.GetBuilding());
}

bool Unit::CollideWith(const Fence &that) const{
    return geo2d::Collide(position_, that.GetFence());
}

bool Unit::CollideWith(const Tower &that) const{
    return geo2d::Collide(position_, that.GetTower());
}

bool Unit::CollideWith(const Unit &that) const{
    return geo2d::Collide(position_, that.GetUnit());
}

const geo2d::Point Unit::GetUnit() const {
    return position_;
}




bool Building::CollideWith(const Building &that) const{
    return geo2d::Collide(geometry_, that.GetBuilding());
}

bool Building::CollideWith(const Fence &that) const{
    return geo2d::Collide(geometry_, that.GetFence());
}

bool Building::CollideWith(const Tower &that) const{
    return geo2d::Collide(geometry_, that.GetTower());
}

bool Building::CollideWith(const Unit &that) const{
    return geo2d::Collide(geometry_, that.GetUnit());
}

geo2d::Rectangle Building::GetBuilding() const{
    return geometry_;
}




bool Tower::CollideWith(const Building &that) const{
    return geo2d::Collide(geometry_, that.GetBuilding());
}

bool Tower::CollideWith(const Fence &that) const{
    return geo2d::Collide(geometry_, that.GetFence());
}

bool Tower::CollideWith(const Tower &that) const{
    return geo2d::Collide(geometry_, that.GetTower());
}

bool Tower::CollideWith(const Unit &that) const{
    return geo2d::Collide(geometry_, that.GetUnit());
}

const geo2d::Circle Tower::GetTower() const{
    return geometry_;
}




bool Fence::CollideWith(const Building &that) const{
    return geo2d::Collide(geometry_, that.GetBuilding());
}
bool Fence::CollideWith(const Fence &that) const{
    return geo2d::Collide(geometry_, that.GetFence());
}
bool Fence::CollideWith(const Tower &that) const{
    return geo2d::Collide(geometry_, that.GetTower());
}
bool Fence::CollideWith(const Unit &that) const{
    return geo2d::Collide(geometry_, that.GetUnit());
}
const geo2d::Segment Fence::GetFence() const{
    return geometry_;
}




bool Collide(const GameObject& first, const GameObject& second) {
    return first.Collide(second);
}



#endif //TASK_6_GAMEOBJECT_H
