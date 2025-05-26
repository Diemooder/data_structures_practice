class polynomial:
	def __init__(self, values):
		self.degree = len(values)
		self.values = values

def poly_add(polA, polB):
	z = []
	posA = posB = posC = 0
	degreeA = polA.degree
	degreeB = polB.degree
	degreeC = max(degreeA, degreeB)
	while(posA <= degreeA and posB <= degreeB):
		if degreeA > degreeB:
			z.append(a.coef[posA])
			posA += 1
			degreeA -= 1
		elif degreeA == degreeB:
			z.append(polA.values[posA] + polB.values[posB])
			posA += 1
			posB += 1
			degreeA -= 1
			degreeB -= 1
		else:
			z.append(b.coef[posB])
			posB += 1
			degreeB -= 1
	return polynomial(z)
