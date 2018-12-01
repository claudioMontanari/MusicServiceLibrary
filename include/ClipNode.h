//
// Created by Claudio Montanari on 14/11/2018.
//

#ifndef MUSICLIBRARYSERVICE_CLIPNODE_H
#define MUSICLIBRARYSERVICE_CLIPNODE_H

#include "MusicClipPtr.h"

class ClipNode {
public:
    ClipNode(long int id);

    MusicClipPtr& music_clip()      { return this->music_clip_;};
    ClipNode * next()               { return this->next_;};
    void next(ClipNode * next_el)   { this->next_ = next_el; };
    bool has_next()                 { return this->next_ != NULL; };

private:
    MusicClipPtr music_clip_;
    ClipNode * next_;
};

#endif //MUSICLIBRARYSERVICE_CLIPNODE_H
