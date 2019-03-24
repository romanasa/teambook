pnode Q[107], W[107], E[107];
int tp[107];

pnode merge(pnode L, pnode R) {
	ind = 0;
	while (1) {
		Q[ind] = L, W[ind] = R;
		if (!L) { E[ind++] = R; break; }
		if (!R) { E[ind++] = L; break; }
		if (L->prior > R->prior) {
			L = L->R;
			tp[ind] = 0;
		} else {
			R = R->L;
			tp[ind] = 1;
		}
		ind++;
	}
	for (int i = ind - 2; i >= 0; i--) {
		if (tp[i] == 0) {
			Q[i]->R = E[i + 1], upd(Q[i]);
			E[i] = Q[i];
		} else {
			W[i]->L = E[i + 1], upd(W[i]);
			E[i] = W[i];
		}
	}
	return E[0];
}

pair<pnode, pnode> split(pnode T, int key) {
	ind = 0;
	while (1) {
		E[ind] = T;
		if (!T) {
			Q[ind] = W[ind] = NULL, ind++;
			break;
		}
		if (T->key <= key) T = T->R, tp[ind] = 0;
		else T = T->L, tp[ind] = 1;
		ind++;
	}
	for (int i = ind - 2; i >= 0; i--) {
		if (tp[i] == 0) {
			E[i]->R = Q[i + 1], upd(E[i]);
			Q[i] = E[i], W[i] = W[i + 1];
		} else {
			E[i]->L = W[i + 1], upd(E[i]);
			Q[i] = Q[i + 1], W[i] = E[i];
		}
	}
	return { Q[0], W[0] };
}