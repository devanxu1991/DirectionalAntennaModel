#ifndef CONIC_ANTENNA_MODEL_H
#define CONIC_ANTENNA_MODEL_H


#include <ns3/object.h>
#include <ns3/antenna-model.h>
#include<vector>

namespace ns3 {


class ConicAntennaModel : public AntennaModel
{
public:

  // inherited from Object
  static TypeId GetTypeId ();

  // inherited from AntennaModel
  double GetGainDb (Angles a);
  // attribute getters/setters
  void SetBeamwidth (double beamwidthDegrees);
  double GetBeamwidth () const;
  void SetOrientation (double orientationDegrees);
  double GetOrientation () const;
  void SetInclination (double inclinationDegrees);
  double GetInclination () const;

  Vector  CalculateAngles(Vector b);

private:
  double m_antennaorientationRadians;
  double m_antennainclinationRadians;
  double m_beamwidthRadians;
};



} // namespace ns3


#endif // CONIC_ANTENNA_MODEL_H
