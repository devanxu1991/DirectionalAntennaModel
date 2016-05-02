#include <ns3/log.h>
#include <ns3/test.h>
#include <ns3/double.h>
#include <ns3/conic-antenna-model.h>
#include <ns3/simulator.h>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("TestConicAntennaModel");

enum ConicAntennaModelGainTestCondition  {
  EQUAL = 0,
  LESSTHAN = 1
};

class ConicAntennaModelTestCase : public TestCase
{
public:
  static std::string BuildNameString (Vector3D v, double b, double ao, double ai);
  ConicAntennaModelTestCase (Vector3D v, double b, double ao, double ai, double expectedGainDb, ConicAntennaModelGainTestCondition cond);


private:
  virtual void DoRun (void);

  Vector3D m_v;
  double m_b;
  double m_o;
  double m_i;
  double m_expectedGain;
  ConicAntennaModelGainTestCondition m_cond;
};

std::string ConicAntennaModelTestCase::BuildNameString (Vector3D v, double b, double ao, double ai)
{
  std::ostringstream oss;
  oss <<  "x=" << v.x << " , y=" << v.y
		<<", z="<<v.z
      << ", beamdwidth=" << b << "deg"
      << ", antennaorientation=" << ao<<"deg"
      << ", antennainclination=" << ai << " deg";
  return oss.str ();
}

ConicAntennaModelTestCase::ConicAntennaModelTestCase (Vector3D v, double b, double ao, double ai, double expectedGainDb, ConicAntennaModelGainTestCondition cond)
  : TestCase (BuildNameString (v, b, ao, ai)),
    m_v (v),
    m_b (b),
    m_o (ao),
    m_i (ai),
    m_expectedGain (expectedGainDb),
    m_cond (cond)
{
}

void
ConicAntennaModelTestCase::DoRun ()
{
  NS_LOG_FUNCTION (this << BuildNameString (m_v, m_b, m_o, m_i));

  Ptr<ConicAntennaModel> a = CreateObject<ConicAntennaModel> ();
  a->SetAttribute ("AntennaBeamwidth", DoubleValue (m_b));//这是用于命令行改变值
  a->SetAttribute ("AntennaOrientation", DoubleValue (m_o));
  a->SetAttribute ("AntennaInclination", DoubleValue (m_i));
  Vector3D vab=a->CalculateAngles(m_v);
  double actualGain = a->GetGainDb (vab);
  switch (m_cond) 
    {
    case EQUAL:
      NS_TEST_EXPECT_MSG_EQ_TOL (actualGain, m_expectedGain, 0.001, "wrong value of the radiation pattern");
      break;
    case LESSTHAN:
      NS_TEST_EXPECT_MSG_LT (actualGain, m_expectedGain, "gain higher than expected");
      break;
    default:
      break;
    }
}
class ConicAntennaModelTestSuite : public TestSuite
{
public:
  ConicAntennaModelTestSuite ();
};

ConicAntennaModelTestSuite::ConicAntennaModelTestSuite ()
  : TestSuite ("conic-antenna-model", UNIT)
{ 
	//分别赋值,b的位置，波宽度，方位角，天顶角，期望天线增益，条件
        //此处改变b节点位置坐标，期望天线增益20dB和-20dB，波束宽度为60度，方位角45度，天顶角45度，
	AddTestCase (new ConicAntennaModelTestCase (Vector3D(0.0,0.0,3.0), 60, 0,  0,  20,     EQUAL), TestCase::QUICK);
	AddTestCase (new ConicAntennaModelTestCase (Vector3D(0.0,0.0,3.0), 60, 10,  10,  20,     EQUAL), TestCase::QUICK);
	AddTestCase (new ConicAntennaModelTestCase (Vector3D(0.0,0.0,3.0), 180, 10,  45,  20,     EQUAL), TestCase::QUICK);
	AddTestCase (new ConicAntennaModelTestCase (Vector3D(0.0,1.0,1.0), 60, 45,  45,  -20,     EQUAL), TestCase::QUICK);
	AddTestCase (new ConicAntennaModelTestCase (Vector3D(0.0,3.0,0.0), 60, 45,  45, -20,     EQUAL), TestCase::QUICK);
	AddTestCase (new ConicAntennaModelTestCase (Vector3D(0.0,0.0,3.0), 90, 45,  45,  -20,     EQUAL), TestCase::QUICK);
	AddTestCase (new ConicAntennaModelTestCase (Vector3D(0.0,0.0,3.0), 60, 5,  45,  -20,     EQUAL), TestCase::QUICK);
	AddTestCase (new ConicAntennaModelTestCase (Vector3D(5.0,-5.0,3.0), 60, 45,  45,  20,     EQUAL), TestCase::QUICK);
   AddTestCase (new ConicAntennaModelTestCase (Vector3D(2.0,0.0,3.0), 60, 45,  45,  -20,     EQUAL), TestCase::QUICK);
	AddTestCase (new ConicAntennaModelTestCase (Vector3D(1.0,1.0,3.0), 60, 45,  45,  -20,     EQUAL), TestCase::QUICK);

};

static ConicAntennaModelTestSuite staticParabolicAntennaModelTestSuiteInstance;
