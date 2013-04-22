#include <string>
#include <iostream>

#include "emulator.h"
#include "fceu/driver.h"
#include "simplefm2.h"

int main (int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "usage: %s [game.nes] [movie.fm2]\n", argv[0]);
    return 1;
  }

  string game_file(argv[1]), movie_file(argv[2]);

  clog << "Loading " << game_file << "..." << endl;


  Emulator::Initialize(game_file);

  clog << "Loading " << movie_file << "..." << endl;

  vector<uint8> movie = SimpleFM2::ReadInputs(movie_file);
  // TODO: get savestate from fm2 file then:
  // Emulator::LoadUncompressed(savestate);

  vector<uint8> mem;

  int frameNo = 0;
  for (uint8 &input : movie) {
    Emulator::Step(input);
    Emulator::GetMemory(&mem);

    clog << frameNo++ << ": H Pos: " << (int)mem[0x6D] << " " << (int)mem[0x86]
        << endl;
  }

  Emulator::Shutdown();

  // exit the infrastructure
  FCEUI_Kill();

  return 0;
}
