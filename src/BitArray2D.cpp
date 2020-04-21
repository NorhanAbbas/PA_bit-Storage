//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <math.h>
#include "BitArray2D.hpp"

   /**
    * Sets up the array to store rows * columns bits
    * @param rows - number of rows
    * @param columns - number of columns
    */
BitArray2D::BitArray2D(unsigned int rows, unsigned int columns) {
        if (rows < 1 || columns < 1 ){
                throw BitArray2DException("Nah! not working");
            }

            else {

            this->rows = rows;
            this->columns = columns;
        }

}


   /**
    * Deallocate memory used for array
    */
BitArray2D::~BitArray2D() {

}

   /**
    * Get bit at row and column
    * @param row
    * @param column
    * @return bit at row and column as bool
    */
bool BitArray2D::get(unsigned int row, unsigned int column){
   // check array bounds

   if (row < 0 || row >= rows){
        throw BitArray2DException("Row number is out of Bounds!");
   }

   if (column < 0 || column >= columns) {
        throw BitArray2DException("Column number is out of Bounds!");
   }

   // get the element
   return get_bit_elem(array, columns, row, column);
}


   /**
    * Set bit to true at row and column
    * @param row
    * @param column
    */
void BitArray2D::set(unsigned int row, unsigned int column){
   // check array bounds

      if (row < 0 || row >= rows){
           throw BitArray2DException("Row number is out of Bounds!");
      }

      if (column < 0 || column >= columns) {
           throw BitArray2DException("Column number is out of Bounds!");
      }

   // set the element
   set_bit_elem(array, columns, row, column);
}
