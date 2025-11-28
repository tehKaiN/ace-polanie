/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <fmt/format.h>
#include "common/bitmap.hpp"
#include "common/lodepng.hpp"

using namespace std::string_literals;

class tLargeBitmapDef {
public:
  std::vector<std::uint8_t> m_vSubbitmaps;
  std::string m_Name;
  std::uint8_t m_ubPaletteIndex;

  tLargeBitmapDef(
    const std::string &Name,
    std::uint8_t ubPaletteIndex,
    const std::vector<std::uint8_t> &vSubbitmaps
  ):
    m_vSubbitmaps(vSubbitmaps),
    m_Name(Name),
    m_ubPaletteIndex(ubPaletteIndex)
  {}

  tChunkyBitmap composeFrom(FILE *pGraphicfile, FILE *pPaletteFile);
};

static std::vector<tLargeBitmapDef> s_LargeBitmaps = {
  tLargeBitmapDef("bg_village", 0, {0, 15}),
  tLargeBitmapDef("menu_save", 1, {1, 16}),
  tLargeBitmapDef("menu_main", 2, {2, 17}),
  tLargeBitmapDef("game_1", 3, {3, 18}),
  tLargeBitmapDef("game_2", 3, {4, 19}),
  tLargeBitmapDef("game_3", 3, {5, 20}),
  tLargeBitmapDef("menu_campaign", 6, {6, 21}),
  tLargeBitmapDef("game_4", 3, {7, 22}),
  tLargeBitmapDef("bg_obelisk", 8, {8, 23}), // palette guessed
  tLargeBitmapDef("logo_topware", 9, {9, 25}), // off by 1
  tLargeBitmapDef("menu_campaign_select", 10, {10, 24}), // off by 1
  tLargeBitmapDef("bg_defeated", 11, {11, 26}),
  tLargeBitmapDef("menu_campaign_borders", 6, {12, 27}),
  tLargeBitmapDef("menu_options", 12, {13, 28}),
  tLargeBitmapDef("bg_offering", 13, {14, 29}), // palette guessed
};

static tChunkyBitmap loadPcImage(FILE *pGraphicfile, int ubImageIndex, const tPalette &Palette)
{
  tChunkyBitmap OutBitmap(319, 100);

  auto FileOffset = ubImageIndex * 33000;
  uint16_t size;

  fseek(pGraphicfile, FileOffset, SEEK_SET);
  fread(&size, sizeof(size), 1, pGraphicfile);
  fread(&size, sizeof(size), 1, pGraphicfile);
  fread(&size, sizeof(size), 1, pGraphicfile);

  for (int16_t wRow = 0; wRow < OutBitmap.m_uwHeight; wRow++) {
    std::uint8_t pRow[319];
    size = std::uint16_t(fread(
      pRow,
      1, 319,
      pGraphicfile
    ));

    for(std::uint16_t x = 0; x < size; ++x) {
      OutBitmap.pixelAt(x, wRow) = Palette.m_vColors[pRow[x]];
    }
  }

  return OutBitmap;
}


tPalette loadPalette(FILE *pPaletteFile, std::uint8_t ubPaletteIndex)
{
  std::vector<tRgb> vColors;
  vColors.resize(256);

  std::uint32_t ulPaletteOffset = ubPaletteIndex * 768;
  fseek(pPaletteFile, ulPaletteOffset, SEEK_SET);
  for(auto i = 0; i < 256; ++i) {
    std::uint8_t r, g, b;
    fread(&r, 1, 1, pPaletteFile);
    fread(&g, 1, 1, pPaletteFile);
    fread(&b, 1, 1, pPaletteFile);
    vColors[i] = tRgb(r, g, b);
  }

  tPalette OutPalette(vColors);
  return OutPalette;
}

tChunkyBitmap tLargeBitmapDef::composeFrom(FILE *pGraphicfile, FILE *pPaletteFile)
{
  auto PartWidth = 319;
  auto PartHeight = 100;
  auto Palette = loadPalette(pPaletteFile, m_ubPaletteIndex);
  auto OutBitmap = tChunkyBitmap(319, PartHeight * m_vSubbitmaps.size());
  for(auto i = 0; i < m_vSubbitmaps.size(); ++i) {
    auto Part = loadPcImage(pGraphicfile, m_vSubbitmaps[i], Palette);
    Part.copyRect(0, 0, OutBitmap, 0, PartHeight * i, Part.m_uwWidth, PartHeight);
  }
  return OutBitmap;
}


int main(int lArgCount, const char *pArgs[])
{
  auto *pGraphicfile = fopen("GRAF.DAT", "rb");
  auto *pPaletteFile = fopen("PAL.DAT", "rb");

  // auto Palette = loadPalette(pPaletteFile, 3);
  // for(uint8_t ubImageIndex = 0; ubImageIndex <= 29; ++ubImageIndex) {
  //   auto Chunky = loadPcImage(pGraphicfile, ubImageIndex, Palette);
  //   Chunky.toPng(fmt::format("out_{0}.png", ubImageIndex));
  // }

  for(uint8_t i = 0; i < s_LargeBitmaps.size(); ++i) {
    auto LargeBitmap = s_LargeBitmaps[i].composeFrom(pGraphicfile, pPaletteFile);
    LargeBitmap.toPng(fmt::format("{0}.png", s_LargeBitmaps[i].m_Name));
  }

  fclose(pGraphicfile);
  fclose(pPaletteFile);
	return EXIT_SUCCESS;
}
