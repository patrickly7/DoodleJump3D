#include "MySolver.h"
using namespace Simplex;

// MySolver
void MySolver::Init(void)
{
	m_v3Acceleration = ZERO_V3;
	m_v3Position = ZERO_V3;
	m_v3Velocity = ZERO_V3;
	m_fMass = 1.0f;
}

void MySolver::Swap(MySolver& other)
{
	std::swap(m_v3Acceleration, other.m_v3Acceleration);
	std::swap(m_v3Velocity, other.m_v3Velocity);
	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_fMass, other.m_fMass);
}

void MySolver::Release(void){ /*nothing to deallocate*/ }

// The Big 3
MySolver::MySolver(void){ Init(); }

MySolver::MySolver(MySolver const& other)
{
	m_v3Acceleration = other.m_v3Acceleration;
	m_v3Velocity = other.m_v3Velocity;
	m_v3Position = other.m_v3Position;
	m_fMass = other.m_fMass;
}

MySolver& MySolver::operator=(MySolver const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MySolver temp(other);
		Swap(temp);
	}
	return *this;
}

MySolver::~MySolver() { Release(); }

// Accessors
void MySolver::SetPosition(vector3 a_v3Position) { m_v3Position = a_v3Position; }
vector3 MySolver::GetPosition(void) { return m_v3Position; }

void MySolver::SetSize(vector3 a_v3Size) { m_v3Size = a_v3Size; }
vector3 MySolver::GetSize(void) { return m_v3Size; }

void MySolver::SetVelocity(vector3 a_v3Velocity) { m_v3Velocity = a_v3Velocity; }
vector3 MySolver::GetVelocity(void) { return m_v3Velocity; }

void MySolver::SetMass(float a_fMass) { m_fMass = a_fMass; }
float MySolver::GetMass(void) { return m_fMass; }

void MySolver::SetOnAir(bool a_isOnAir) { m_onAir = a_isOnAir; }
bool MySolver::GetOnAir(void) { return m_onAir; }

// Methods
vector3 CalculateMaxVelocity(vector3 a_v3Velocity, float maxVelocity)
{
	if (glm::length(a_v3Velocity) > maxVelocity)
	{
		a_v3Velocity = glm::normalize(a_v3Velocity);
		a_v3Velocity *= maxVelocity;
	}
	return a_v3Velocity;
}

vector3 RoundSmallVelocity(vector3 a_v3Velocity, float minVelocity = 0.01f)
{
	if (glm::length(a_v3Velocity) < minVelocity)
	{
		a_v3Velocity = ZERO_V3;
	}
	return a_v3Velocity;
}

void MySolver::ApplyFriction(float a_fFriction)
{
	if (a_fFriction < 0.01f)
		a_fFriction = 0.01f;
	
	m_v3Velocity *= 1.0f - a_fFriction;
	m_v3Velocity = RoundSmallVelocity(m_v3Velocity, m_minVelocity);
}

void MySolver::ApplyForce(vector3 a_v3Force)
{
	if (m_fMass < 0.01f)
		m_fMass = 0.01f;
	
	m_v3Acceleration += a_v3Force / m_fMass;
}

void MySolver::Update(void)
{
	// Apply Force of Gravity
	ApplyForce(m_v3Gravity);
	m_v3Velocity += m_v3Acceleration;
	m_v3Velocity = CalculateMaxVelocity(m_v3Velocity, m_maxVelocity);

	// Apply Friction to Reduce Velocity
	ApplyFriction(m_friction);
	m_v3Velocity = RoundSmallVelocity(m_v3Velocity, m_minVelocity);

	m_v3Position += m_v3Velocity;
	if (m_v3Position.y <= -25.0f)
	{
		m_v3Position.y = -25.0f;
		m_v3Velocity.y = 0;
	}

	// Reset Acceleration
	m_v3Acceleration = ZERO_V3;
}

void MySolver::ResolvePlayerToPlatform(MySolver* a_pPlatform)
{
	if (m_v3Position.y < a_pPlatform->m_v3Position.y)
	{
		m_v3Position.y = a_pPlatform->m_v3Position.y;
	}

	if (m_v3Velocity.y <= 0)
	{
		m_onAir = false;
	}
}

void MySolver::ResolvePlayerToSpikeBed(MySolver* a_pSpikeBed)
{
	// TODO - Game Over
}

void MySolver::ResolvePlayerToWall(MySolver* a_pWall)
{
	if (m_v3Position.x > 0.0f)
		m_v3Position.x -= 1.0f;
	else
		m_v3Position.x += 1.0f;

	if (m_v3Position.z > 0.0f)
		m_v3Position.z -= 1.0f;
	else
		m_v3Position.z += 1.0f;

	m_v3Velocity = vector3(-m_v3Velocity.x, m_v3Velocity.y, -m_v3Velocity.z);
}

void MySolver::ResolvePlatformToSpikeBed(MySolver* a_pSpikeBed)
{
	// TODO - What happens when a platform touches the spikes?
	// Currently the "other" is the platform, "this" is spikebed
	if (m_v3Position.y < a_pSpikeBed->m_v3Position.y)
	{
		m_v3Position.y = a_pSpikeBed->m_v3Position.y;
	}
}