"use strict";

const ALLOWED_METHODS = new Set([
  "GET",
  "POST",
  "PUT",
  "PATCH",
  "DELETE",
  "OPTIONS",
]);

function cleanAuthBaseUrl(value) {
  if (!value) {
    throw new Error("NEON_AUTH_URL is missing.");
  }

  const cleaned = value
    .trim()
    .replace(/^["']|["']$/g, "")
    .replace(/\/+$/, "");

  const parsed = new URL(cleaned);

  if (parsed.protocol !== "https:" && parsed.protocol !== "http:") {
    throw new Error("NEON_AUTH_URL must start with https:// or http://");
  }

  return cleaned;
}

function cleanAuthPath(value) {
  const path = Array.isArray(value) ? value[0] : value;

  if (!path || typeof path !== "string") {
    throw new Error("Missing authentication path.");
  }

  const decoded = decodeURIComponent(path);

  if (
    !decoded.startsWith("/") ||
    decoded.startsWith("//") ||
    decoded.includes("\\") ||
    decoded.includes("..") ||
    decoded.startsWith("/api/")
  ) {
    throw new Error("Invalid authentication path.");
  }

  return decoded;
}

function requestBody(req) {
  if (req.method === "GET" || req.method === "HEAD") {
    return undefined;
  }

  if (req.body === undefined || req.body === null) {
    return undefined;
  }

  if (Buffer.isBuffer(req.body) || typeof req.body === "string") {
    return req.body;
  }

  return JSON.stringify(req.body);
}

function copySetCookies(upstream, res) {
  if (typeof upstream.headers.getSetCookie === "function") {
    const cookies = upstream.headers.getSetCookie();

    if (cookies.length > 0) {
      res.setHeader("Set-Cookie", cookies);
    }

    return;
  }

  const cookie = upstream.headers.get("set-cookie");

  if (cookie) {
    res.setHeader("Set-Cookie", cookie);
  }
}

module.exports = async function handler(req, res) {
  res.setHeader("Cache-Control", "no-store");

  if (!ALLOWED_METHODS.has(req.method)) {
    return res.status(405).json({
      code: "METHOD_NOT_ALLOWED",
      message: "Method not allowed.",
    });
  }

  if (req.method === "OPTIONS") {
    res.setHeader("Allow", Array.from(ALLOWED_METHODS).join(", "));
    return res.status(204).end();
  }

  try {
    const authBaseUrl = cleanAuthBaseUrl(process.env.NEON_AUTH_URL);
    const authPath = cleanAuthPath(req.query.path);
    const targetUrl = `${authBaseUrl}${authPath}`;

    const headers = {
      accept: req.headers.accept || "application/json",
    };

    if (req.headers["content-type"]) {
      headers["content-type"] = req.headers["content-type"];
    } else if (req.body !== undefined) {
      headers["content-type"] = "application/json";
    }

    if (req.headers.authorization) {
      headers.authorization = req.headers.authorization;
    }

    if (req.headers.cookie) {
      headers.cookie = req.headers.cookie;
    }

    if (req.headers.origin) {
      headers.origin = req.headers.origin;
    }

    if (req.headers.referer) {
      headers.referer = req.headers.referer;
    }

    if (req.headers["user-agent"]) {
      headers["user-agent"] = req.headers["user-agent"];
    }

    const upstream = await fetch(targetUrl, {
      method: req.method,
      headers,
      body: requestBody(req),
      redirect: "manual",
    });

    const contentType = upstream.headers.get("content-type");
    const location = upstream.headers.get("location");

    if (contentType) {
      res.setHeader("Content-Type", contentType);
    }

    if (location) {
      res.setHeader("Location", location);
    }

    copySetCookies(upstream, res);

    const responseBody = Buffer.from(await upstream.arrayBuffer());

    return res.status(upstream.status).send(responseBody);
  } catch (error) {
    console.error("Neon Auth proxy failed:", error);

    return res.status(502).json({
      code: "AUTH_SERVICE_UNAVAILABLE",
      message:
        error instanceof Error
          ? error.message
          : "Authentication service is temporarily unavailable.",
    });
  }
};