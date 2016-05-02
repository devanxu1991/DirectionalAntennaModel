#ifndef DIRECTIONAL_PROPAGATION_LOSS_MODEL_H
#define DIRECTIONAL_PROPAGATION_LOSS_MODEL_H

#include <ns3/object.h>
#include <ns3/propagation-loss-model.h>

namespace ns3 {

class MobilityModel;
class DirectionalPropagationLossModel : public PropagationLossModel
{
public:
	  static TypeId GetTypeId (void);
	  DirectionalPropagationLossModel ();
	  virtual ~DirectionalPropagationLossModel ();
	  void SetMaximumDistance (double maximumDistance);
	  double GetMaximumDistance(void) const;
private:
  DirectionalPropagationLossModel (const DirectionalPropagationLossModel &);
  DirectionalPropagationLossModel &operator = (const DirectionalPropagationLossModel&);
  virtual double DoCalcRxPower (double txPowerDbm,
                                Ptr<MobilityModel> a,
                                Ptr<MobilityModel> b) const;
  int64_t DoAssignStreams (int64_t stream);
 double m_maximumDistance;
};
} // namespace ns3
#endif /* DIRECTIONAL_PROPAGATION_LOSS_MODEL_H */
