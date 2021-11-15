//
// Created by antoo on 10/11/2021.
//

#ifndef RAT_IDISPLAY_H
#define RAT_IDISPLAY_H


class IDisplay {
public:
    virtual void waiting();
    virtual void reading();
    virtual void success();
    virtual void turnOff();
};


#endif //RAT_IDISPLAY_H
