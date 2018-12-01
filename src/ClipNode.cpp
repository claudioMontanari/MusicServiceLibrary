//
// Created by Claudio Montanari on 16/11/2018.
//

#include "../include/ClipNode.h"

ClipNode::ClipNode(long int id) {
    music_clip_ = MusicClipPtr(id);
    next_ = NULL;
}

