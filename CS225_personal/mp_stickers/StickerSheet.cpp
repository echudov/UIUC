#include "StickerSheet.h"
#include "Image.h"
#include <vector>
#include <tuple>
#include <algorithm>

typedef std::vector<std::tuple<Image, std::tuple<unsigned int, unsigned int>>> stickerType;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    max_ = max;
    base = picture;
    count_ = 0;
    stickers.resize(max);
}

StickerSheet::~StickerSheet() {
    clear();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void StickerSheet::clear() {
    stickers.clear();
}

void StickerSheet::copy(const StickerSheet &other) {
    max_ = other.max_;
    base = other.base;
    count_ = other.count_;
    this->stickers = other.stickers;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    max_ = max;
    if (max < count_) {
        count_ = max;
    }
    stickers.resize(max);
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (count_ == max_) {
        // stickers.push_back(std::make_tuple(sticker, std::make_tuple(x, y)));
        return -1;
    }
    else  {
        stickers[count_++] = std::make_tuple(sticker, std::make_tuple(x, y));
        return count_ - 1;
    }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < 0 || index >= count_) {
        return false;
    }
    std::get<1>(stickers[index]) = std::make_tuple(x, y);
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < 0 || index >= count_) {
        return;   
    }
    count_--;
    stickers.erase(stickers.begin() + index);
    this->changeMaxStickers(max_);
}
Image * StickerSheet::getSticker(unsigned index) {
    if (index >= count_) {
        return NULL;
    }
    return &(std::get<0>(stickers[index]));
}

Image StickerSheet::render() {
    Image toReturn(base);
    for (unsigned int i = 0; i < count_; i++) {
        auto &sticker = stickers[i];
        Image &s = std::get<0>(sticker);
        unsigned int x0 = std::get<0>(std::get<1>(sticker));
        unsigned int y0 = std::get<1>(std::get<1>(sticker));
        if (x0 + s.width() > toReturn.width() || y0 + s.height() > toReturn.height()) {
            toReturn.resize(std::max(toReturn.width(), x0 + s.width()), std::max(toReturn.height(), y0 + s.height()));
        }
        for (unsigned int x = x0; x < x0 + s.width(); ++x) {
            for (unsigned int y = y0; y < y0 + s.height(); ++y) {
                cs225::HSLAPixel &pix = s.getPixel(x - x0, y - y0);
                if (pix.a == 0) {
                    continue;
                } else {
                    toReturn.getPixel(x, y) = pix;
                }
            }
        }
    }
    return toReturn;
}