using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class CharacterMakingManager : MonoBehaviour {
	[SerializeField]
	Image characterImage;

	[SerializeField]
	Sprite spriteTori;

	[SerializeField]
	Sprite spriteKuma;

	[SerializeField]
	Sprite spriteNeko;

	[SerializeField]
	Toggle check;
	
	[SerializeField]
	Mask mask;
	
	[SerializeField]
	RawImage rimg;
	
	[SerializeField]
	GameObject sclbar;
	
	[SerializeField]
	GameObject sclbar2;

	[SerializeField]
	Slider sld;

	public void OnClickCharacterTori(){
		characterImage.sprite = spriteTori;
	}

	public void OnClickCharacterKuma(){
		characterImage.sprite = spriteKuma;
	}

	public void OnClickCharacterNeko(){
		characterImage.sprite = spriteNeko;
	}

	public void OnClickDisplayAll(){
		mask.gameObject.GetComponent<Mask>().enabled = !check.isOn;
		rimg.gameObject.GetComponent<RawImage>().enabled = !check.isOn;
		sclbar.SetActive(!check.isOn);
		//sclbar2.SetActive(!check.isOn);
		if (check.isOn == true) {
			characterImage.gameObject.transform.localPosition = new Vector3(-22,-73,0);
		}
	}
	public void OnChangeFill(){
		characterImage.fillAmount = sld.value;
	}

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
