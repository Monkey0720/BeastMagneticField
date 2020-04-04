
#include <vector>

#include <math.h>

#ifndef _BEAST_MAGNETIC_FIELD_
#define _BEAST_MAGNETIC_FIELD_

// Well, one can of course determine this from the input data, but what's the point?;
#define _CELL_SIZE_               (2.0)

// See the original solenoid.C script; prefer to indicate a cutoff;
#define _CRYOSTAT_INNER_RADIUS_ (137.0)

struct BeastMagneticFieldCell {
public:
  BeastMagneticFieldCell(float r, float z, float br, float bz): mR(r), mZ(z), mBR(br), mBZ(bz) {};
  ~BeastMagneticFieldCell() {};

  float mR, mZ, mBR, mBZ;
};

class BeastMagneticField {
public:
  // Argument is the ASCII file name with the Elmer map;
  BeastMagneticField(const char *fname, bool enforce_axial_symmetry = true);
  ~BeastMagneticField() {};

  bool ValidMapImported( void ) const { return mFieldMap; };

  // Ignore the z-coordinate I guess?;
  bool IsInsideTheBore(double x, double y/*, double z*/) {
    return (sqrt(x*x+y*y) < _CRYOSTAT_INNER_RADIUS_);
  };

  void UseInterpolation( void ) { mUseInterpolation = true; };
  bool GetFieldValue(double x, double y, double z, double &bx, double &by, double &bz) const;
  // Field has an axial symmetry -> provide a simplified call as well;
  bool GetFieldValue(double r, double z, double &br, double &bz) const;

 private:
  // Input map grid cell size; assume a square in {RZ}; may want to extract 
  // this value from the data later, so make it a variable;
  double mCellSize;

  // Grid size in radial distance from the solenoid symmetry axis and 
  // along the symmetry axis;
  unsigned mRdim, mZdim;

  // Map edge (min. radius and min. Z; well, mRmin should better be 0.0;
  double mRmin, mZmin;

  // Default: no interpolation, return the grid values;
  bool mUseInterpolation;
  std::pair<double, double> *mFieldMap;
};

#endif