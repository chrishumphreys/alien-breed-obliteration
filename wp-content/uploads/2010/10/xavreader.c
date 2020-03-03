/*	
	Written By:
 		Chris Humphreys
 		Email: < chris (--AT--) habitualcoder [--DOT--] com >
 
 	Copyright HabitualCoder 2010
 
	This file is part of alien breen obliteration wii edition
 
 	This program is free software; you can redistribute it and/or modify
 	it under the terms of the GNU General Public License as published by
 	the Free Software Foundation; either version 3 of the License, or
 	(at your option) any later version.
 
 	This program is distributed in the hope that it will be useful,
 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 	GNU General Public License for more details.
 
 	You should have received a copy of the GNU General Public License
 	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// xavreader.c : Read encoded and deflated file from XAV archive

#include <stdio.h> 
#include <stdlib.h>
#include "string.h"
#include "zlib.h"

#define ENCODED_NAME "%s/encoded-%%s"
#define DECRYPTED_NAME "%s/decrypted-%%s"
#define FINAL_NAME "%s/%%s"

#define DEBUG 0

/* Details of the encrypted and packed data within the XAV archive */
struct EncodedFile {
	char *filename;
	long offset;
	int length;
	char *encodedBuffer;
	char *decryptedBuffer;
	char *decryptedFilename;
};

int process_file(char *filename, long offset, int length, char *archiveFile);

char *encodedPath;
char *decryptedPath;
char *finalPath;

int main(int argc, char **argv)
{
	char *archiveFile;
	char *tmpPath;
	char *finalDir;

	if (argc != 4) {
		printf("Syntax: xavreader <xav file> <tmpdir> <finaldir>\n");
		printf("e.g. xavreader data1.xav /tmp ./\n");
		exit(1);
	}

	archiveFile = argv[1];
	tmpPath = argv[2];
	finalDir = argv[3];

	encodedPath = (char *) malloc (sizeof(char)*(strlen(tmpPath)+strlen(ENCODED_NAME)+10));
	sprintf(encodedPath, ENCODED_NAME, tmpPath);
	decryptedPath = (char *) malloc (sizeof(char)*(strlen(tmpPath)+strlen(DECRYPTED_NAME)+10));
	sprintf(decryptedPath, DECRYPTED_NAME, tmpPath);
	finalPath = (char *) malloc (sizeof(char)*(strlen(finalDir)+strlen(FINAL_NAME)+10));
	sprintf(finalPath, FINAL_NAME, finalDir);

	printf("Reading %s\n", archiveFile);
	printf("Writing tmp files to %s, %s\n", encodedPath, decryptedPath);
	printf("Output to %s\n", finalPath);


	//Name, offset, len
	//details captured using uHooker python module
	process_file("airfan.bmp",0x14,0x704, archiveFile);
	process_file("airvent.bmp",0x7B3,0x4E9, archiveFile);
	process_file("alienhead.bmp",0xD45,0x1F5C, archiveFile);
	process_file("allweaps.bmp", 0x2D55, 0xA8DA, archiveFile);
	process_file("barrel.bmp", 0xD62F, 0x16F, archiveFile);
	process_file("bigmenuselector.bmp",0xDCF3,0x2EB, archiveFile);
	process_file("biopod.bmp", 0xE1A5, 0x36C, archiveFile);
	process_file("biospike.bmp", 0xE677, 0x3FF, archiveFile);
	process_file("boss1.bmp", 0xEB4E, 0x2A0A, archiveFile);
	process_file("boss2.bmp", 0x1168D, 0x1CA6, archiveFile);
	process_file("boss3.bmp", 0x13464, 0x1C0B, archiveFile);
	process_file("boss4.bmp", 0x15199, 0x260D, archiveFile);
	process_file("breedfont.bmp",0x179F0,0x460, archiveFile);
	process_file("bullet.bmp", 0x17F70, 0x105, archiveFile);
	process_file("countdown.bmp", 0x18075, 0xEF, archiveFile);
	process_file("cursor.bmp", 0x18164, 0x3E, archiveFile);
	process_file("decklift.bmp", 0x18245, 0x4BF2, archiveFile);
	process_file("deckman.bmp",0x1CEA0,0x5DF, archiveFile);
	process_file("deckstart.bmp",0x1D47F,0x6620, archiveFile);
	process_file("demoScreen1.bmp",0x25013,0x13A5, archiveFile);
	process_file("demoScreen2.bmp",0x263B8,0x1553, archiveFile);
	process_file("demoScreen3.bmp",0x2790B,0x190E, archiveFile);
	process_file("demoScreen4.bmp",0x29219,0x144E, archiveFile);
	process_file("demoScreen5.bmp",0x2A667,0x9BD, archiveFile);
	process_file("developer.bmp",0x2B024,0x508, archiveFile);
	process_file("domel.bmp", 0x2B8A0, 0x272C, archiveFile);
	process_file("doorfirehorizontal.bmp", 0x2DFCC, 0x23D, archiveFile);
	process_file("doorfireverticle.bmp", 0x2E2E8, 0x24E, archiveFile);
	process_file("doorhorizontal.bmp",0x2E614,0x2C6, archiveFile);
	process_file("doorvertical.bmp",0x2E9C4,0x275, archiveFile);
	process_file("egg.bmp", 0x2ED20, 0x2EF, archiveFile);
	process_file("ending.bmp", 0x2F0EC, 0x2E5A, archiveFile);
	process_file("enemy1.bmp", 0x31F46, 0x1E23, archiveFile);
	process_file("enemy2.bmp", 0x33F2F, 0x2052, archiveFile);
	process_file("enemy3.bmp", 0x36152, 0x1D8D, archiveFile);
	process_file("enemy4.bmp", 0x380AF, 0x20B3, archiveFile);
	process_file("enemy5.bmp", 0x3A333, 0xB71, archiveFile);
	process_file("enemy6.bmp",0x3B074,0x205C, archiveFile);
	process_file("enemy7.bmp", 0x3D2A2, 0x9C2, archiveFile);
	process_file("enemy8.bmp", 0x3DE34, 0x2059, archiveFile);
	process_file("explosionbig.bmp", 0x40458, 0x64B, archiveFile);
	process_file("forcefieldhorizontal.bmp", 0x41BBF, 0x40A, archiveFile);
	process_file("gameover1.bmp", 0x42F53, 0x15D, archiveFile);
	process_file("gameover2.bmp", 0x430B0, 0x1CA, archiveFile);
	process_file("gameover3.bmp", 0x4327A, 0x235, archiveFile);
	process_file("gameover4.bmp", 0x434AF, 0x243, archiveFile);
	process_file("gameover5.bmp", 0x436F2, 0x2B5, archiveFile);
	process_file("gameover6.bmp", 0x439A7, 0x3BB, archiveFile);
	process_file("gameover7.bmp", 0x43D62, 0x473, archiveFile);
	process_file("gameover8.bmp", 0x441D5, 0x5A6, archiveFile);
	process_file("gameover9.bmp", 0x4477B, 0x50D, archiveFile);
	process_file("greenfont.bmp",0x44D93,0x3F0, archiveFile);
	process_file("gunfire.bmp",0x45183,0x114, archiveFile);
	process_file("hostage.bmp", 0x45371, 0x40A, archiveFile);
	process_file("hud.bmp",0x45860,0x2E5, archiveFile);	
	process_file("hudgold.bmp",0x45B45,0x5F, archiveFile);
	process_file("hudgoldplus.bmp",0x45BA4,0xF6, archiveFile);
	process_file("IntexBG.bmp", 0x45C9A, 0x59FD, archiveFile);
	process_file("lift.bmp",0x66829,0x19A, archiveFile);
	process_file("mapbits.bmp", 0x66AEA, 0x47, archiveFile);
	process_file("menuselect.bmp",0x66BAF,0x362, archiveFile);
	process_file("miscbits.bmp",0x66F11,0xA0A, archiveFile);
	process_file("passblue.bmp",0x67AFD,0x130, archiveFile);
	process_file("player1.bmp",0x68302,0x25BB, archiveFile);
	process_file("player2.bmp", 0x6AA66, 0x259D, archiveFile);
	process_file("securitycomp.bmp", 0x6D1A5, 0x1233, archiveFile);
	process_file("ship.bmp", 0x6E4A0, 0x1AB4, archiveFile);
	process_file("shipfire.bmp", 0x6FFE1, 0x1C3, archiveFile);
	process_file("shippod.bmp", 0x70269, 0x96A, archiveFile);
	process_file("spawner2.bmp", 0xE6637, 0x1EF, archiveFile);
	process_file("spawner3.bmp", 0xE68FD, 0x1E9, archiveFile);
	process_file("spawner4.bmp", 0xE6BBD, 0x1B8, archiveFile);
	process_file("spawner5.bmp", 0xE6E4C, 0x181, archiveFile);
	process_file("spawner6.bmp",0xE70A5,0x202, archiveFile);
	process_file("spawner7.bmp", 0xE737F, 0x155, archiveFile);
	process_file("spawner8.bmp", 0xE75AC, 0x20F, archiveFile);
	process_file("spawner.bmp",0xE636B,0x1F6, archiveFile);
	process_file("switch.bmp", 0xE7893, 0x277, archiveFile);
	process_file("tileset1.bmp",0xE7C11,0x2A965, archiveFile);
	process_file("tinyfont.bmp", 0x114118, 0x361, archiveFile);
	process_file("tinymenuselect.bmp",0x114479,0x329, archiveFile);
	process_file("trigger.bmp", 0x114A99, 0x6D, archiveFile);


	process_file("airfan.uni",0x718,0x9B, archiveFile);
	process_file("airvent.uni",0xC9C,0xA9, archiveFile);
	process_file("barrel.uni", 0xD79E, 0xEA, archiveFile);
	process_file("biopodb.uni", 0xE511, 0xB2, archiveFile);
	process_file("biopodf.uni", 0xE5C3, 0xB4, archiveFile);
	process_file("biospike.uni", 0xEA76, 0xD8, archiveFile);
	process_file("boss1.uni", 0x11558, 0x135, archiveFile);
	process_file("boss2.uni", 0x13333, 0x131, archiveFile);
	process_file("boss3.uni", 0x1506F, 0x12A, archiveFile);
	process_file("boss4.uni", 0x177A6, 0x132, archiveFile);
	process_file("dome.uni", 0x2B7C9, 0xD7, archiveFile);
	process_file("doorfirehorizontal.uni", 0x2E209, 0xDF, archiveFile);
	process_file("doorfireverticle.uni", 0x2E536, 0xDE, archiveFile);
	process_file("doorhorizontal.uni",0x2E8DA,0xEA, archiveFile);
	process_file("doorverticle.uni",0x2EC39,0xE7, archiveFile);
	process_file("egg.uni", 0x2F00F, 0xDD, archiveFile);
	process_file("enemy1.uni", 0x33D69, 0x1C6, archiveFile);
	process_file("enemy2.uni", 0x35F81, 0x1D1, archiveFile);
	process_file("enemy3.uni", 0x37EDF, 0x1D0, archiveFile);
	process_file("enemy4.uni", 0x3A162, 0x1D1, archiveFile);
	process_file("enemy5.uni", 0x3AEA4, 0x1D0, archiveFile);
	process_file("enemy6.uni",0x3D0D0,0x1D2, archiveFile);
	process_file("enemy7.uni", 0x3DC64, 0x1D0, archiveFile);
	process_file("enemy8.uni", 0x3FE8D, 0x1D2, archiveFile);
	process_file("enemy9.uni", 0x4005F, 0x1D0, archiveFile);
	process_file("explosionbig.uni", 0x40AA3, 0x115, archiveFile);
	process_file("explosionsmall.uni", 0x40BB8, 0xB9, archiveFile);
	process_file("firebossworm.uni", 0x4133A, 0x1BC, archiveFile);
	process_file("fireflamearch.uni", 0x414F6, 0x10A, archiveFile);
	process_file("fireflamethrower.uni", 0x41600, 0x10F, archiveFile);
	process_file("firelazer.uni", 0x4170F, 0xF0, archiveFile);
	process_file("firemachinegun.uni", 0x417FF, 0xED, archiveFile);
	process_file("fireplasmagun.uni", 0x418EC, 0xF0, archiveFile);
	process_file("firesidewinder.uni", 0x419DC, 0xF5, archiveFile);
	process_file("firetwinfire.uni", 0x41AD1, 0xEE, archiveFile);
	process_file("forcefieldhorizontal.uni", 0x41FC9, 0xAA, archiveFile);
	process_file("GameEndText.txt", 0x4255A, 0x179, archiveFile);
	process_file("gamemenuentertainment.txt", 0x426D3, 0x8F, archiveFile);
	process_file("gamemenuintro.txt", 0x42E63, 0xD3, archiveFile);
	process_file("gamemenuoutro.txt", 0x42F36, 0x1D, archiveFile);
	process_file("gunfire.uni",0x45297,0xDA, archiveFile);
	process_file("hostage.uni", 0x4577B, 0xE5, archiveFile);
	process_file("gamemenuinfo.txt", 0x42762, 0x701, archiveFile);
	process_file("level10.lev", 0x4CBB7, 0x68E, archiveFile);
	process_file("level10.til", 0x4D245, 0x1C5D, archiveFile);
	process_file("level11.lev", 0x4EEA2, 0x679, archiveFile);
	process_file("level11.til", 0x4F51B, 0x1EE7, archiveFile);
	process_file("level12.lev", 0x51402, 0x2CF, archiveFile);
	process_file("level12.til", 0x516D1, 0xF4F, archiveFile);
	process_file("level13.lev", 0x52620, 0x655, archiveFile);
	process_file("level13.til", 0x52C75, 0xE3A, archiveFile);
	process_file("level14.lev", 0x53AAF, 0x31D, archiveFile);
	process_file("level14.til", 0x53DCC, 0x5CE, archiveFile);
	process_file("level15.lev", 0x5439A, 0x4F7, archiveFile);
	process_file("level15.til", 0x54891, 0x174A, archiveFile);
	process_file("level1.lev",0x4B697,0x4B7, archiveFile);
	process_file("level1.til",0x4BB4E,0x1069, archiveFile);
	process_file("level2.lev", 0x55FDB, 0x63E, archiveFile);
	process_file("level2.til",0x56619,0x187E, archiveFile);
	process_file("level3.lev", 0x57E97, 0x95B, archiveFile);
	process_file("level3.til", 0x587F2, 0x25EF, archiveFile);
	process_file("level4.lev", 0x5ADE1, 0x21C, archiveFile);
	process_file("level4.til", 0x5AFFD, 0x12D3, archiveFile);
	process_file("level5.lev", 0x5C2D0, 0x60E, archiveFile);
	process_file("level5.til", 0x5C8DE, 0x16AF, archiveFile);
	process_file("level6.lev", 0x5DF8D, 0x6E9, archiveFile);
	process_file("level6.til", 0x5E676, 0x2191, archiveFile);
	process_file("level7.lev", 0x60807, 0x80B, archiveFile);
	process_file("level7.til", 0x61012, 0x2045, archiveFile);
	process_file("level8.lev", 0x63057, 0x7CE, archiveFile);
	process_file("level8.til", 0x63825, 0x13E4, archiveFile);
	process_file("level9.lev", 0x64C09, 0x7ED, archiveFile);
	process_file("level9.til", 0x653F6, 0x1433, archiveFile);
	process_file("lift.uni",0x669C3,0xA4, archiveFile);
	process_file("pickupammo.uni",0x67C2D,0xD8, archiveFile);
	process_file("pickupbluepass.uni", 0x67D05, 0xF5, archiveFile);
	process_file("pickupcredit10000.uni", 0x67FAD, 0xDA, archiveFile);
	process_file("pickupcredit1000.uni",0x67ED3,0xDA, archiveFile);
	process_file("pickupcredit100.uni",0x67DFA,0xD9, archiveFile);
	process_file("pickupfirstaid.uni", 0x68087, 0xD7, archiveFile);
	process_file("pickupkey.uni",0x6815E,0xD4, archiveFile);
	process_file("pickuplife.uni", 0x68232, 0xD0, archiveFile);
	process_file("Player1.uni",0x6A8BD,0x1A9, archiveFile);
	process_file("player2.uni", 0x6D003, 0x1A2, archiveFile);
	process_file("securitycomp.uni", 0x6E3D8, 0xC8, archiveFile);
	process_file("shipfire.uni", 0x701A4, 0xC5, archiveFile);
	process_file("shippod.uni", 0x70BD3, 0x8F, archiveFile);
	process_file("ship.uni", 0x6FF54, 0x8D, archiveFile);
	process_file("spawner2.uni", 0xE6826, 0xD7, archiveFile);
	process_file("spawner3.uni", 0xE6AE6, 0xD7, archiveFile);
	process_file("spawner4.uni", 0xE6D75, 0xD7, archiveFile);
	process_file("spawner5.uni", 0xE6FCD, 0xD8, archiveFile);
	process_file("spawner6.uni",0xE72A7,0xD8, archiveFile);
	process_file("spawner7.uni", 0xE74D4, 0xD8, archiveFile);
	process_file("spawner8.uni", 0xE77BB, 0xD8, archiveFile);
	process_file("spawner.uni",0xE6561,0xD6, archiveFile);
	process_file("switch.uni", 0xE7B0A, 0x107, archiveFile);
	process_file("tileset1.map",0x112576,0x1983, archiveFile);
	process_file("toolsandweapons.wep",0x11482E,0x26B, archiveFile);
	process_file("trigger.uni", 0x114B06,0xA8, archiveFile);
	

	process_file("aliendie1.ogg", 0x72531, 0x16B0, archiveFile);
	process_file("aliendie2.ogg", 0x73BE1, 0x1E38, archiveFile);
	process_file("ammo.ogg", 0x77795, 0x1C8B, archiveFile);
	process_file("background.ogg", 0x79420, 0x146B, archiveFile);
	process_file("blip2.ogg", 0x7B55B, 0xC9C, archiveFile);
	process_file("blip.ogg", 0x7A88B, 0xCD0, archiveFile);
	process_file("compend.ogg", 0x7FA44, 0x1223, archiveFile);
	process_file("compstart.ogg", 0x80C67, 0x1D60, archiveFile);
	process_file("door.ogg", 0x829C7, 0x1AA0, archiveFile);
	process_file("endlev.xm", 0x92D7C, 0x26E8, archiveFile);
	process_file("end.xm", 0x8771F, 0xB65D, archiveFile);
	process_file("explodesmall.ogg", 0x98C6F, 0x1409, archiveFile);
	process_file("gundouble.ogg", 0x9B303, 0x1951, archiveFile);
	process_file("gunfire.ogg", 0x9CC54, 0xD7F, archiveFile);
	process_file("gunflamearc.ogg", 0x9D9D3, 0x1440, archiveFile);
	process_file("gunflamer.ogg", 0x9EE13, 0x1923, archiveFile);
	process_file("gunlazer.ogg", 0xA0736, 0xFCF, archiveFile);
	process_file("gunplasma.ogg", 0xA1705, 0x1A66, archiveFile);
	process_file("gunsidewinder.ogg", 0xA316B, 0x1780, archiveFile);
	process_file("key.ogg", 0xA48EB, 0x1959, archiveFile);
	process_file("life.ogg", 0xA6244, 0x1E75, archiveFile);
	process_file("lift.ogg",0xA80B9,0x71D2, archiveFile);
	process_file("menu.xm",0xAF28B,0x15058, archiveFile);
	process_file("money.ogg", 0xC42E3, 0x1390, archiveFile);
	process_file("pass.ogg",0xC5673,0x195B, archiveFile);
	process_file("playerdie.ogg", 0xC6FCE, 0x184F, archiveFile);
	process_file("Ricochet.ogg", 0xC881D, 0x1129, archiveFile);
	process_file("shotdoor.ogg", 0xC9946, 0x196D, archiveFile);
	process_file("shotnoammo.ogg", 0xCB2B3, 0xE57, archiveFile);
	process_file("siren.ogg", 0xCC10A, 0x16D8, archiveFile);
	process_file("voc_aid.ogg", 0xD6793, 0x4D13, archiveFile);
	process_file("vocdestruction2.ogg", 0xD2E50, 0x3943, archiveFile);
	process_file("vocdestruction.ogg", 0xCD7E2, 0x566E, archiveFile);
	process_file("voc_key.ogg", 0xDB4A6, 0x429D, archiveFile);
	process_file("welcome.ogg", 0xDF743, 0x6C28, archiveFile);

	free(encodedPath);
	free(decryptedPath);
	free(finalPath);
}


/*
	Read the encrypted and packed data from XAV archive
	decrypt using password
	inflate using zLib
	Save target file
*/

int read_encoded_data(struct EncodedFile *encodedFile, char* archiveFile);
int decrypt_packed_data(struct EncodedFile *encodedFile);
int unpack(struct EncodedFile *packedFile);

int process_file(char *filename, long offset, int length, char* archiveFile) {
	int result;

	struct EncodedFile tinyFont;
	tinyFont.filename = filename;
	tinyFont.offset = offset;
	tinyFont.length = length;
	tinyFont.encodedBuffer = NULL;
	tinyFont.decryptedBuffer = NULL;
	tinyFont.decryptedFilename = NULL;

	result = read_encoded_data(&tinyFont, archiveFile);
	if (!result) {
		result = decrypt_packed_data(&tinyFont);
		if (!result) {
			unpack(&tinyFont);
		}
	}
	if (!result) {
		if (tinyFont.encodedBuffer != NULL) {
			free(tinyFont.encodedBuffer);
		}
		if (tinyFont.decryptedBuffer != NULL) {
			free((void *)tinyFont.decryptedBuffer);
		}
		if (tinyFont.decryptedFilename != NULL) {
			free((void *)tinyFont.decryptedFilename);
		}
	} else {
		perror("Failed to read:" );
		perror(tinyFont.filename);
	}

	return result;
}


/*
Extract the encoded (and packed) data from the file given name, offset and length
*/
int read_encoded_data(struct EncodedFile *encodedFile, char *archiveFile) {
	FILE* f_read;
	FILE* f_write;
	char* buffer;
	int read = 0;
	char outputName [50];

	if(DEBUG) {
		printf("Extracting encoded data for %s...", encodedFile->filename);
	}

	f_read = fopen(archiveFile, "rb");
	if (!f_read) {
		perror("Failed opening file for reading:");
		return(1);
	}

	fseek(f_read, encodedFile->offset, SEEK_SET);

	buffer = (char*) malloc (sizeof(char)*encodedFile->length);
	read = fread(buffer, 1, encodedFile->length, f_read);

	if (read == encodedFile->length) {

		if(DEBUG) {
			sprintf (outputName, ENCODED_NAME, encodedFile->filename);
			if (DEBUG) {
				printf("Writing encoded file %s", outputName);
			}
			f_write = fopen ( outputName , "wb" );
			fwrite (buffer , 1 , encodedFile->length , f_write );
			fclose(f_write);
		}

		encodedFile->encodedBuffer = buffer;
    }
	else {
		perror("fread error ");
	}

	if (fclose(f_read) == EOF) {
		perror("Failed closing file");
		return(1);
	}

	return 0;
}


/*
Decrypt the packed data
*/

const
  unsigned long magic_lookup [256] = {
       0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3, 
       0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 
       0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7, 
       0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5, 
       0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, 
       0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59, 
       0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F, 
       0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D, 
       0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433, 
       0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01, 
       0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 
       0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65, 
       0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB, 
       0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, 
       0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F, 
       0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD, 
       0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683, 
       0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1, 
       0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7, 
       0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 
       0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B, 
       0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79, 
       0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, 
       0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D, 
       0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713, 
       0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 
       0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777, 
       0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45, 
       0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB, 
       0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9, 
       0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF, 
       0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
   };

// return the MSB of the LSW of the supplied dword
int ah(int dword){
	return (dword &0xff00) >> 8;
}

// return the LSB of the LSW of the supplied dword
int al(int dword){
	return (dword &0xff);
}

struct  MagicWords {
	int word_1;
	int word_2;
	int word_3;
};

int partial_decode_byte(int encoded_byte, int magic_word_3);
void update_magic_words(struct MagicWords *magic_words, int partial_decode_byte);

int decrypt_packed_data(struct EncodedFile *encodedFile)
{
	unsigned char* result;
	struct MagicWords magic_words;
	FILE* f_write;
	char outputName [50];

	//The magic words must represent the password used to encoded the packed file
	//Every file uses the same password...
	magic_words.word_1 = 0x12e07897;
	magic_words.word_2 = 0x2f2dbb3d;
	magic_words.word_3 = 0x1bbdc9ae;

	int encoded_length = encodedFile->length;
	int current_char_index = 0;

	int current_working_char;
	int working_num = 0;

	result = (unsigned char*) malloc (sizeof(char)*encoded_length);

	if (DEBUG) {
		printf("Starting decode...\n");
	}

	for (current_char_index=0; current_char_index < encoded_length; current_char_index++) {
		current_working_char = encodedFile->encodedBuffer[current_char_index];
		if(DEBUG) {
			printf("******* Encoded byte %x\n", current_working_char);
		}
		working_num = partial_decode_byte(current_working_char, magic_words.word_3);
		if(DEBUG) {
			printf("******* Partially decoded byte %x\n", working_num);
		}
		result[current_char_index] = working_num;
		update_magic_words(&magic_words, working_num);
	}
	
	if (DEBUG) {
		printf("Finished decoding");
		printf("Decrypted data:\n");
		for (current_char_index=0; current_char_index < encoded_length; current_char_index++) {
			if (current_char_index % 16 == 0) {
				printf("\n");
			}
			printf("%x ", result[current_char_index]);
		}
	}

	sprintf (outputName, decryptedPath, encodedFile->filename);
	if (DEBUG) {
		printf("Writing decrypted file %s", outputName);
	}
	f_write = fopen ( outputName , "wb" );
	fwrite (result , 1 , encodedFile->length , f_write );
	fclose(f_write);

	encodedFile->decryptedFilename = (char*) malloc (sizeof(char)* strlen(outputName)+4);
	strcpy(encodedFile->decryptedFilename,outputName);

	return 0;
}

void update_magic_words(struct MagicWords *magic_words, int partial_decode_byte){
	int working_num1, working_num2, working_num3 = 0;

	//Call AlienBre.00423A80
	if(DEBUG) {
		printf("Updating magic words...\n");
		printf("EAX = %x\n",magic_words->word_1);
		printf("ECX = %x\n", partial_decode_byte);
	}
	working_num1 = partial_decode_byte ^ magic_words->word_1;
	if(DEBUG) {
		printf("ECX = %x\n",working_num1);
	}
	working_num2 = magic_words->word_1 >> 8;
	working_num2 &= 0x00ffffff;
	if(DEBUG) {
		printf("EAX = %x\n",working_num2);
	}
	working_num1 &= 0xff;
	if(DEBUG) {
		printf("ECX = %x\n",working_num1);
	}
	working_num1 = magic_lookup[working_num1];
	if(DEBUG) {
		printf("ECX = %x\n",working_num1);
	}
	working_num1 ^= working_num2;
	if(DEBUG) {
		printf("%x\n",working_num1);
	}
	working_num2 = al(working_num1);
	if(DEBUG) {
		printf("%x\n",working_num2);
	}
	working_num2 += magic_words->word_2;
	if(DEBUG) {
		printf("%x\n",working_num2);
	}
	magic_words->word_1=working_num1;
	working_num2*=0x8088405;
	if(DEBUG) {
		printf("%x\n",working_num2);
	}
	working_num2+=1;
	if(DEBUG) {
		printf("%x\n",working_num2);
	}
	magic_words->word_2 = working_num2;
	if(DEBUG) {
		printf("%x\n",working_num2);
	}
	working_num2 = working_num2 >> 0x18;
	working_num2 &= 0x000000ff;
	if(DEBUG) {
		printf("%x\n",working_num2);
	}
	working_num2 ^= magic_words->word_3;
	if(DEBUG) {
		printf("%x\n",working_num2);
	}
	working_num2 &= 0xff;
	if(DEBUG) {
		printf("%x\n",working_num2);
	}
	working_num1 = magic_words->word_3;
	if(DEBUG) {
		printf("%x\n",working_num1);
	}
	working_num1 = working_num1 >> 8;
	working_num1 &= 0x00ffffff;
	if(DEBUG) {
		printf("ECX = %x\n",working_num1);
	}
	working_num3 = magic_lookup[working_num2];
	if(DEBUG) {
		printf("%x\n",working_num3);
	}
	working_num1 ^= working_num3;
	if(DEBUG) {
		printf("%x\n",working_num1);
	}
	magic_words->word_3 = working_num1;

	if(DEBUG) {
		printf("Magic nums:\n%x\n%x\n%x\n", magic_words->word_1, magic_words->word_2, magic_words->word_3);
	}
}

int partial_decode_byte(int encoded_byte, int magic_word_3) {
	int working_num,working_num2,working_num3 = 0;

	//Call AlienBre.00423AD0 
	//Appears to calculate a mask for the encoded byte
	working_num = magic_word_3;
	if(DEBUG) {
		printf("%x\n", working_num);
	}
	working_num &= 0xfffd;
	if(DEBUG) {
		printf("%x\n", working_num);
	}
	working_num |= 2;
	if(DEBUG) {
		printf("%x\n", working_num);
	}
	working_num2 = working_num;
	working_num2 ^= 1;
	if(DEBUG) {
		printf("%x\n", working_num2);
	}
	working_num = working_num * working_num2;
	if(DEBUG) {
		printf("%x\n", working_num);
	}

	working_num3 = ah(working_num);
	working_num &= 0xffffff00;
	working_num |= working_num3;
	if(DEBUG) {
		printf("%x\n", working_num);
		printf("%x    %x\n", encoded_byte, al(working_num));
	}

	encoded_byte ^= al(working_num);
	if(DEBUG) {
		printf("%x\n", encoded_byte);
	}

	return encoded_byte;
}



/*
Unpack the compressed data
*/
int inf(FILE *source, FILE *dest);

int unpack(struct EncodedFile *packedFile) {
	char outputName [50];
	FILE *f_read;
	FILE *f_write;

	f_read = fopen(packedFile->decryptedFilename, "rb");
	if (!f_read) {
		perror("Failed opening file for reading:");
		return(1);
	}

	//skip the first 12 bytes (not part of the zLib stream)
	fseek(f_read, 12, SEEK_SET);

	sprintf (outputName, finalPath, packedFile->filename);
	f_write = fopen ( outputName , "wb" );
	if (!f_write) {
		perror("Failed opening file for writing (unpacked):");
		return(1);
	}
	
	inf(f_read, f_write);

	fclose(f_write);
	fclose(f_read);

}

/*
Inflate the packed data using zLib Inflate
Copied and modified from
   zpipe.c: example of proper use of zlib's inflate() and deflate()
   Not copyrighted -- provided to the public domain
   Version 1.4  11 December 2005  Mark Adler 
*/

#define CHUNK 16384

/* Decompress from file source to file dest until stream ends or EOF.
   inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_DATA_ERROR if the deflate data is
   invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
   the version of the library linked do not match, or Z_ERRNO if there
   is an error reading or writing the files. */
int inf(FILE *source, FILE *dest)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    //ret = inflateInit(&strm);
	ret = inflateInit2(&strm, -15);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            //assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}
