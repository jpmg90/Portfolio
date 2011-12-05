using UnityEngine;
using System.Collections;

public class CrumblingPlatformScript : MonoBehaviour 
{

	private int MAX_COUNTER = 20;
	public int timeCounter = 1;
	bool touch = false;
	protected GameObject player;
	void Start()
	{
		player = GameObject.FindGameObjectWithTag("Player");
		
		if(timeCounter > MAX_COUNTER)
			timeCounter = MAX_COUNTER;
	}
	public virtual void OnCollisionStay(Collision info)
	{
			//if player, apply bump damage
			if(info.collider.tag == player.tag)
			{
				if(touch == false)
				{
					StartCoroutine(subtractCounter());
				}
			
				if(timeCounter <= 0)
				{
					// Add Particle Effect for breaking block
					Destroy(this.gameObject);
				}
			}
	}	
	IEnumerator subtractCounter()
	{
		touch = true;
		yield return new WaitForSeconds(1);
		timeCounter --;
		touch = false;
	}
	void OnDestroy()
	{
		player.GetComponent<BaseCharacter>().OnGround = false;
	}
	
}
