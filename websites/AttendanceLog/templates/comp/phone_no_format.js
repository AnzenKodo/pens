const phone_no = document.querySelector("input[name='phone_no']");
phone_no.addEventListener("paste", (e) => {
	e.stopPropagation();
	e.preventDefault();

	const data = e.clipboardData.getData('Text');
	if (data.startsWith("+91")) {
		e.target.value = "";
		e.target.value = data.slice(0, 13);
	}
})
