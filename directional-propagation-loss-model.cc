#include "ns3/directional-propagation-loss-model.h"
#include "ns3/conic-antenna-model.h"
#include "ns3/mobility-model.h"
#include "ns3/log.h"
#include "ns3/double.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include <cmath>
#include <vector>

class ConicAntennaModel;
namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (DirectionalPropagationLossModel);

TypeId
DirectionalPropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DirectionalPropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .SetGroupName ("Propagation")
    .AddConstructor<DirectionalPropagationLossModel> ()
    .AddAttribute ("MaximumDistance",
	                   "The maximum distance between a and b,which is calculated (m)",
	                   DoubleValue (300.0),
	                   MakeDoubleAccessor (&DirectionalPropagationLossModel::m_maximumDistance),
	                   MakeDoubleChecker<double> ())
	  ;
	  return tid;
}
int64_t
DirectionalPropagationLossModel::DoAssignStreams (int64_t stream)
{
  return 0;
}

DirectionalPropagationLossModel::DirectionalPropagationLossModel ()
:m_maximumDistance(300.0)
{
}
DirectionalPropagationLossModel::~DirectionalPropagationLossModel ()
{
}
void
DirectionalPropagationLossModel::SetMaximumDistance(double maximumDistance)
{
	m_maximumDistance = maximumDistance;
}
double
DirectionalPropagationLossModel::GetMaximumDistance(void) const
{
  return m_maximumDistance;
}
double
DirectionalPropagationLossModel::DoCalcRxPower (double txPowerDbm,
                                                Ptr<MobilityModel> a,
                                                Ptr<MobilityModel> b) const

{
  double distance = a->GetDistanceFrom (b);
  if (distance <= m_maximumDistance)
   {
	  Vector3D a_position=a->GetPosition();
	  Vector3D b_position=b->GetPosition();
	  Ptr<ConicAntennaModel> ainstance= CreateObject<ConicAntennaModel> ();
	  Vector b_relativeantennaposition= ainstance->CalculateAngles(b_position);
	  double gt =  ainstance->GetGainDb (b_relativeantennaposition);
	  Ptr<ConicAntennaModel> binstance= CreateObject<ConicAntennaModel> ();
	  Vector a_relativeantennaposition=  binstance->CalculateAngles(a_position);
	  double gr=  binstance->GetGainDb (a_relativeantennaposition);
	 return txPowerDbm *gt*gr;
   }
  else return 0;

}

}
