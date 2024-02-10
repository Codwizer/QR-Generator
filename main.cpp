// TODO: Customize the solution, move away from libqrencode, and implement our own solution

#include <iostream>
#include <string>
#include "qrencode.h"

// QRCode Generations
// Author: CodWiz
// I did it for GitHub
// License: MIT

int margin = 2;

// This function just creates lines of blank space.
std::string makeASCII_margin(int realwidth, int invert)
{
  int y, h;

  h = margin;

  std::string output;
  std::string oneline;
  for(y = 0; y < realwidth; y++) {
    oneline += (invert?"\u2588":" ");
  }
  oneline += "\n";
  for(y = 0; y < h; y++) {
    output += oneline;
  }
  return output;
}

// Draw QR Code
std::string makeASCII(const QRcode *qrcode, int invert) {
  std::string image;
  unsigned char *row;
  std::string black = "\u2588";
  std::string white = " ";
  int y, x;

  if (invert) {
    black = " ";
    white = "\u2588";
  }

  int realwidth = (qrcode->width + margin * 2) * 2;
  std::string buffer;

  image += makeASCII_margin(realwidth, invert);

  for(y = 0; y < qrcode->width; y++) {
    row = qrcode->data+(y*qrcode->width);

    for (x = 0; x < margin*2; x++) {
      image += white;
    }

    for(x = 0; x < qrcode->width; x++) {
      if(row[x]&0x1) {
        image += black;
        image += black;
      } else {
        image += white;
        image += white;
      }
    }

    for (x = 0; x < margin*2; x++) {
      image += white;
    }
    image += "\n";
  }

  image += makeASCII_margin(realwidth, invert);

  return image;

}

int main() {
  std::cout << R"( _____ ______                   _       
|  _  || ___ \                 | |      
| | | || |_/ /  ___   ___    __| |  ___ 
| | | ||    /  / __| / _ \  / _` | / _ \
\ \/' /| |\ \ | (__ | (_) || (_| ||  __/
 \_/\_\\_| \_| \___| \___/  \__,_| \___|
  )";
  std::cout << "--Generator--\n\n";

  QRcode *qrcode;

  std::string input;
  std::cout << "Enter the text for the qr code: ";
  std::getline(std::cin, input);

  const char* stringData = input.c_str();

  qrcode = QRcode_encodeString(stringData, 1, QR_ECLEVEL_M, QR_MODE_8, 0);
  qrcode->width = 21;
  std::cout << "QR Size:" << qrcode->width << std::endl;

  if (qrcode == NULL) {
    std::cout << "qrcode generation failed" << std::endl;
    if(errno == ERANGE) {
      fprintf(stderr, "Failed to encode the input data: Input data too large\n");
    } else {
      perror("Failed to encode the input data");
    }

  } else {
    std::string output = makeASCII(qrcode, 1);
    std::cout << output << std::endl;
  }

  return 0;
}
