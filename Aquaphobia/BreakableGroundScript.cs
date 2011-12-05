using UnityEngine;
using System.Collections;

public class BreakableGroundScript : MonoBehaviour 
{
	private int MAX_COUNTER = 10;
	public int damageCounter = 2;
	
	void Start()
	{
        // Checks to make sure damageCounter isn't over max
		if(damageCounter > MAX_COUNTER)
			damageCounter = MAX_COUNTER;
	}
	
	void OnTriggerEnter(Collider other)
	{
		// check if hit by a players attack
		if(collider.enabled)
		{
			// Check if it was hit by slam attack
			// Check if it was hit by an object with the "DestructiveAttack" tag
			GameObject thisObject = other.gameObject;
			if(thisObject.tag == "Destructive Attack")
			{
				damageCounter --;
				if(damageCounter == 0)
				{
					// Add Particle Effect for breaking block
					Destroy(this.gameObject);
				}
			}
		}
	}	
}

