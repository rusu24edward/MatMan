
#include "MatrixBase.h"

int MatrixBase::size(int dim) const {
	if (dim == 1) {
		return nRows;
	} else if (dim == 2) {
		return nCols;
	} else {
		return nRows > nCols ? nRows : nCols;
	}
}




